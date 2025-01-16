#include <utilities/consolidate/merge_processes.hpp>

namespace valik
{

bool merge_processes(search_arguments const & arguments,
                     app::search_time_statistics & time_statistics,
                     app::execution_metadata & exec_meta,
                     env_var_pack const & var_pack)
{
    bool successful_merge{true};
    std::filesystem::path merge_out_path;
    if (arguments.bin_path.size() > 1)  // no need to consolidate metagenome search
        merge_out_path = arguments.out_file;
    else
        merge_out_path = arguments.all_matches;
    std::ofstream matches_out(merge_out_path, std::ofstream::app);

    // merge metadata from all threads
    exec_meta.merge(arguments, time_statistics);
    std::vector<std::string> merge_process_args;
    merge_process_args.push_back("echo");
    if (exec_meta.output_files.size() > 0)
    {
        merge_process_args.push_back(var_pack.merge_exec);
        for (auto & path : exec_meta.output_files)
        {
            merge_process_args.push_back(path);
            if (merge_process_args.size() % 1024 == 0)
            {
                external_process merge(merge_process_args);
                matches_out << merge.cout();
                successful_merge = successful_merge && check_external_process_success(merge_process_args, merge);
                merge_process_args.clear();
                merge_process_args.push_back(var_pack.merge_exec);
            }
        }            
    }

    //!WORKAROUND: merge hangs if no valik matches found or no cat arguments after clear
    if ((exec_meta.output_files.size() == 0) || (merge_process_args.size() == 1))
    {
        merge_process_args.clear();
        merge_process_args.push_back("echo");
        merge_process_args.push_back("-n");
    }

    external_process merge(merge_process_args);
    matches_out << merge.cout();

    for (auto & path : exec_meta.output_files)
    {
        const bool error_in_delete = !std::filesystem::remove(path);
        if (error_in_delete)
            std::cerr << "Could not clean up intermediate file: \t" << std::string(path) << '\n';
    }
    if (exec_meta.output_files.size() > 0)
    {
    	std::filesystem::path stellar_out_dir = std::filesystem::path(exec_meta.output_files[0]).parent_path();
    	if (std::filesystem::is_empty(stellar_out_dir))
    	{
        	const bool error_in_delete = !std::filesystem::remove(stellar_out_dir);
        	if (error_in_delete)
            	std::cerr << "Could not delete folder: " << std::string(stellar_out_dir) << '\n';
    	}
    }
    return successful_merge && check_external_process_success(merge_process_args, merge);
}

}   // namespace valik
