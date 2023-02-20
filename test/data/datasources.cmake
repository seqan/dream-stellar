cmake_minimum_required (VERSION 3.16)

include (cmake/app_datasources.cmake)

declare_datasource (FILE single_query.fq
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single_query.fq
                URL_HASH SHA256=129a0da8803e169cc8f81c46da20e68e4ba8e251e4e979fbecf6466073bf184a)
declare_datasource (FILE single_reference.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single_reference.fasta
                URL_HASH SHA256=53d633474b01a68927d3ab1fd970b200e96403bb1fdcc53feb0367a2093be273)
declare_datasource (FILE various_chromosome_lengths.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/split/various_chromosome_lengths.fasta
                URL_HASH SHA256=7c7a8fcdd52a932cda76219f24024c1624292377103d9fd5a55abd288c6072be)


declare_datasource (FILE 150overlap16bins13window1errors.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap16bins13window1errors.gff
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE 150overlap16bins13window1errors.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap16bins13window1errors.gff.out
                URL_HASH SHA256=adb235de49127905e0b74a35040aa6a3601a7dd060cfd04dfc16783e08b89b3f)
declare_datasource (FILE 150overlap16bins13window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap16bins13window.ibf
                URL_HASH SHA256=bf2db42adc669ab73b074d74758ad56cf35d0c396031a0e73809b659fe8a76ce)
declare_datasource (FILE 150overlap16bins15window1errors.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap16bins15window1errors.gff
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE 150overlap16bins15window1errors.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap16bins15window1errors.gff.out
                URL_HASH SHA256=4d31ba8e86eb7fdf7586a2d7e24955e739087cae5973a7679b7e31e4c3780bfe)
declare_datasource (FILE 150overlap16bins15window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap16bins15window.ibf
                URL_HASH SHA256=cb18705eaa1a94963969e7381efc3b5c099c241d7446a7292203c5d5b434b127)
declare_datasource (FILE 150overlap16bins.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap16bins.txt
                URL_HASH SHA256=39501216962a5103aad09575248167cf5cfa63c96598ea8fcd7134421e1c8504)
declare_datasource (FILE 150overlap4bins13window1errors.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap4bins13window1errors.gff
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE 150overlap4bins13window1errors.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap4bins13window1errors.gff.out
                URL_HASH SHA256=dcbc6727d475f09aa6db6b2f6c3d49917cc37e9d879593d13c27444e53ab5e6c)
declare_datasource (FILE 150overlap4bins13window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap4bins13window.ibf
                URL_HASH SHA256=ce7b31acef135e024af9268b3416030d85e4c2828bc8c5dc3d1f18a34a03d373)
declare_datasource (FILE 150overlap4bins15window1errors.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap4bins15window1errors.gff
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE 150overlap4bins15window1errors.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap4bins15window1errors.gff.out
                URL_HASH SHA256=00f586cc88ee87d0b88f1affe2dbd49b45d6aa650235c390740437c6f8877db4)
declare_datasource (FILE 150overlap4bins15window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap4bins15window.ibf
                URL_HASH SHA256=bc803cda05ef409a258420268d31e7ba3d8a5175b8292175cf40bdab10565ff5)
declare_datasource (FILE 150overlap4bins.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap4bins.txt
                URL_HASH SHA256=cb60eb69a8519bbcb52da3e3f6524d11f560c11d7c70a094697a5f2254500b97)
declare_datasource (FILE reference_metadata.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/reference_metadata.txt
                URL_HASH SHA256=b82abe243ea2872d540d3548759997f93db2345351f76c93dd6ab40992abf1cd)


declare_datasource (FILE 0overlap16bins.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/multi/0overlap16bins.txt
                URL_HASH SHA256=f41420e802d66d96bb3d2246d459791ebe5796da669600552a0c3eb43082345f)
declare_datasource (FILE 0overlap4bins.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/multi/0overlap4bins.txt
                URL_HASH SHA256=171e201e20f2dc9d5d855b753fc7bf6abe7297ded613e727c0ed1dd69bbaf02f)
declare_datasource (FILE 20overlap16bins.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/multi/20overlap16bins.txt
                URL_HASH SHA256=32a40e7211cd45832506f16d0b3a613a222efd0783463978a50aa85ecb302837)
declare_datasource (FILE 20overlap4bins.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/multi/20overlap4bins.txt
                URL_HASH SHA256=171e201e20f2dc9d5d855b753fc7bf6abe7297ded613e727c0ed1dd69bbaf02f)
declare_datasource (FILE chromosome_metadata.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/multi/chromosome_metadata.txt
                URL_HASH SHA256=368803a8d29419321ba9704bc7cbd52abf6f7b2f528d725ed54a5ecadf5c6ae3)


declare_datasource (FILE write_out_0_16_reference_metadata.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/write_out_0_16/reference_metadata.txt
                URL_HASH SHA256=368803a8d29419321ba9704bc7cbd52abf6f7b2f528d725ed54a5ecadf5c6ae3)
declare_datasource (FILE write_out_0_16_reference_segments.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/write_out_0_16/reference_segments.txt
                URL_HASH SHA256=f41420e802d66d96bb3d2246d459791ebe5796da669600552a0c3eb43082345f)
declare_datasource (FILE write_out_0_16_ref.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/split/write_out_0_16/ref.fasta
                URL_HASH SHA256=7c7a8fcdd52a932cda76219f24024c1624292377103d9fd5a55abd288c6072be)
declare_datasource (FILE write_out_0_4_reference_metadata.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/write_out_0_4/reference_metadata.txt
                URL_HASH SHA256=368803a8d29419321ba9704bc7cbd52abf6f7b2f528d725ed54a5ecadf5c6ae3)
declare_datasource (FILE write_out_0_4_reference_segments.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/write_out_0_4/reference_segments.txt
                URL_HASH SHA256=171e201e20f2dc9d5d855b753fc7bf6abe7297ded613e727c0ed1dd69bbaf02f)
declare_datasource (FILE write_out_0_4_ref.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/split/write_out_0_4/ref.fasta
                URL_HASH SHA256=7c7a8fcdd52a932cda76219f24024c1624292377103d9fd5a55abd288c6072be)
declare_datasource (FILE write_out_20_16_reference_metadata.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/write_out_20_16/reference_metadata.txt
                URL_HASH SHA256=368803a8d29419321ba9704bc7cbd52abf6f7b2f528d725ed54a5ecadf5c6ae3)
declare_datasource (FILE write_out_20_16_reference_segments.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/write_out_20_16/reference_segments.txt
                URL_HASH SHA256=32a40e7211cd45832506f16d0b3a613a222efd0783463978a50aa85ecb302837)
declare_datasource (FILE write_out_20_16_ref.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/split/write_out_20_16/ref.fasta
                URL_HASH SHA256=7c7a8fcdd52a932cda76219f24024c1624292377103d9fd5a55abd288c6072be)
declare_datasource (FILE write_out_20_4_reference_metadata.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/write_out_20_4/reference_metadata.txt
                URL_HASH SHA256=368803a8d29419321ba9704bc7cbd52abf6f7b2f528d725ed54a5ecadf5c6ae3)
declare_datasource (FILE write_out_20_4_reference_segments.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/write_out_20_4/reference_segments.txt
                URL_HASH SHA256=171e201e20f2dc9d5d855b753fc7bf6abe7297ded613e727c0ed1dd69bbaf02f)
declare_datasource (FILE write_out_20_4_ref.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/split/write_out_20_4/ref.fasta
                URL_HASH SHA256=7c7a8fcdd52a932cda76219f24024c1624292377103d9fd5a55abd288c6072be)
declare_datasource (FILE 8bins19window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/build/8bins19window.ibf
                URL_HASH SHA256=3a13c890650bf857770816244ed9420295ad8bbe681dac335f687863fc79a603)
declare_datasource (FILE 8bins23window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/build/8bins23window.ibf
                URL_HASH SHA256=250578b9e0c47df929ed628931441ada4569ab7df193a5ecb5c069e6339bd56a)
declare_datasource (FILE bin_0.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/build/bin_0.fasta
                URL_HASH SHA256=f9836f233fe459f8e387f8723dc030a10e44f3490cc1c89bed36222742bd6c35)
declare_datasource (FILE bin_1.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/build/bin_1.fasta
                URL_HASH SHA256=782cb2eb50722e4a4fb2b5ca82b39817bf78305146a0ae086bab3273997e9237)
declare_datasource (FILE bin_2.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/build/bin_2.fasta
                URL_HASH SHA256=5ff43c19f3b2d0d7cd113efd5941ff204a5e31820c6edc49c7c47f2d16388e77)
declare_datasource (FILE bin_3.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/build/bin_3.fasta
                URL_HASH SHA256=0fc4021828129d1752dc2d9a1c163cfb642547ca8e889e969b119e6a2942a39f)
declare_datasource (FILE bin_4.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/build/bin_4.fasta
                URL_HASH SHA256=d62dbba326f03da7fd4f0d61b460efcc73aee52582fc0903f5358978f33d1a9f)
declare_datasource (FILE bin_5.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/build/bin_5.fasta
                URL_HASH SHA256=6f16ee171f262e6d1c621b94563adad42a5aab27afee48340d9c2273e67e396f)
declare_datasource (FILE bin_6.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/build/bin_6.fasta
                URL_HASH SHA256=c4efc778c575e103041b300e0f110677d740c169e55421b9d16650fe92a8c872)
declare_datasource (FILE bin_7.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/build/bin_7.fasta
                URL_HASH SHA256=45063104427a48892ba4ccb45cc295dc94760f08c1db90e6f3a73744591ada68)
declare_datasource (FILE bin_paths.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/build/bin_paths.txt
                URL_HASH SHA256=614e23263b689c7b4cc0ae41e99aeb5b43b351f865b4604f892320f2cc4377c7)


declare_datasource (FILE 8bins19window0error100pattern1overlap.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error100pattern1overlap.gff
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE 8bins19window0error100pattern1overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error100pattern1overlap.gff.out
                URL_HASH SHA256=3c8232f56bb5b48a2c4e8d41dfe377b825e1fb414713505b21ea3501c6ab3f21)
declare_datasource (FILE 8bins19window0error100pattern40overlap.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error100pattern40overlap.gff
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE 8bins19window0error100pattern40overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error100pattern40overlap.gff.out
                URL_HASH SHA256=3c8232f56bb5b48a2c4e8d41dfe377b825e1fb414713505b21ea3501c6ab3f21)
declare_datasource (FILE 8bins19window0error50pattern1overlap.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error50pattern1overlap.gff
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE 8bins19window0error50pattern1overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error50pattern1overlap.gff.out
                URL_HASH SHA256=7e9a0782bfe6dcc969302ef8818d48740bcfa130ae620c4fe9e9cacc7bd877e2)
declare_datasource (FILE 8bins19window0error50pattern40overlap.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error50pattern40overlap.gff
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE 8bins19window0error50pattern40overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error50pattern40overlap.gff.out
                URL_HASH SHA256=cc221a25f15404f1ea0caea27c69567f91090dcffaa4c0847ce57d352c44b48c)
declare_datasource (FILE 8bins19window1error100pattern1overlap.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error100pattern1overlap.gff
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE 8bins19window1error100pattern1overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error100pattern1overlap.gff.out
                URL_HASH SHA256=cda429aaaee2d597bae94efd30ffd018e719094736d8c7e472d1abb37d7c24a7)
declare_datasource (FILE 8bins19window1error100pattern40overlap.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error100pattern40overlap.gff
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE 8bins19window1error100pattern40overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error100pattern40overlap.gff.out
                URL_HASH SHA256=55e2d07ea5d9a26a25754f92c6458a8c444f8aeaa08159424d4481081f1470d4)
declare_datasource (FILE 8bins19window1error50pattern1overlap.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error50pattern1overlap.gff
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE 8bins19window1error50pattern1overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error50pattern1overlap.gff.out
                URL_HASH SHA256=0cb644b16a31b530926c3f44640c898ebf8b5c5a5116a21680504c22d78034fd)
declare_datasource (FILE 8bins19window1error50pattern40overlap.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error50pattern40overlap.gff
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE 8bins19window1error50pattern40overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error50pattern40overlap.gff.out
                URL_HASH SHA256=1a27e6d620fe62983908dd8029de429475f36a362da764498e71c829bb0764b9)
declare_datasource (FILE 8bins23window0error100pattern1overlap.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error100pattern1overlap.gff
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE 8bins23window0error100pattern1overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error100pattern1overlap.gff.out
                URL_HASH SHA256=cfeb2fdc80371ede98bff6b1b25e0eedf19866b9d545bdfd6e9b068dbbf3f7d5)
declare_datasource (FILE 8bins23window0error100pattern40overlap.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error100pattern40overlap.gff
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE 8bins23window0error100pattern40overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error100pattern40overlap.gff.out
                URL_HASH SHA256=cfeb2fdc80371ede98bff6b1b25e0eedf19866b9d545bdfd6e9b068dbbf3f7d5)
declare_datasource (FILE 8bins23window0error50pattern1overlap.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error50pattern1overlap.gff
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE 8bins23window0error50pattern1overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error50pattern1overlap.gff.out
                URL_HASH SHA256=672a78cbf55b92f2b8ec3059a40094a414cce9b5512004e7371b3f3b7278c596)
declare_datasource (FILE 8bins23window0error50pattern40overlap.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error50pattern40overlap.gff
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE 8bins23window0error50pattern40overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error50pattern40overlap.gff.out
                URL_HASH SHA256=fffab0d5dda0486ca236da2ed492febedbd8920fba0eeda7c9e950b7c68471f9)
declare_datasource (FILE 8bins23window1error100pattern1overlap.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error100pattern1overlap.gff
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE 8bins23window1error100pattern1overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error100pattern1overlap.gff.out
                URL_HASH SHA256=b3bda51dd88622e52b0ca58749c5343cdaec06f860e518b1346799a05b7ed177)
declare_datasource (FILE 8bins23window1error100pattern40overlap.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error100pattern40overlap.gff
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE 8bins23window1error100pattern40overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error100pattern40overlap.gff.out
                URL_HASH SHA256=cb7678c4d77278b1419f12cfb6c66ae5b9a568aa6d17d0ada35f40d566626365)
declare_datasource (FILE 8bins23window1error50pattern1overlap.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error50pattern1overlap.gff
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE 8bins23window1error50pattern1overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error50pattern1overlap.gff.out
                URL_HASH SHA256=e3935d90bac2014a385796658daf269bd8e53326e0b28bd0789619d23356d1ff)
declare_datasource (FILE 8bins23window1error50pattern40overlap.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error50pattern40overlap.gff
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE 8bins23window1error50pattern40overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error50pattern40overlap.gff.out
                URL_HASH SHA256=15dafc62819955efed07a1d3880ea7a78ff4464c247de6abc10cd925f58161c2)
declare_datasource (FILE query.fq
                URL ${CMAKE_SOURCE_DIR}/test/data/search/query.fq
                URL_HASH SHA256=4d684a7e4f8b2a9eceb927edaf1a17543c6bbab7efa6a5eedfeb90465caa37ed)


declare_datasource (FILE 10overlap_full.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/10overlap_full.gff
                URL_HASH SHA256=48e79e6cd9c0672a0396eda3c3e27efdac980d6b1d77a7273e8a34859abb4c2a)
declare_datasource (FILE 16bins10overlap_dream_all.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/16bins10overlap_dream_all.gff
                URL_HASH SHA256=955057f355600ec93a965fc9cfca6092f06e6ee3b3fd1f9e6590334381bbd1c5)
declare_datasource (FILE 16bins10overlap_dream_consolidated.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/16bins10overlap_dream_consolidated.gff
                URL_HASH SHA256=296b99ee23f03f859274b88f5f6ffe08ac15a41f419282bf2a608dfdbd0f6ac7)
declare_datasource (FILE 16bins10overlap_reference_metadata.tsv
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/16bins10overlap_reference_metadata.tsv
                URL_HASH SHA256=8ed578817aadb6390957047dad4d16e952325e48824d0a7041f6e6a59414ac3d)
declare_datasource (FILE 16bins50overlap_dream_all.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/16bins50overlap_dream_all.gff
                URL_HASH SHA256=e30f06f9076e45c3cad53fd7ca217f293a546f325fa3d0f448d654607048e44c)
declare_datasource (FILE 16bins50overlap_dream_consolidated.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/16bins50overlap_dream_consolidated.gff
                URL_HASH SHA256=e436b20ab0b35bc0c9bf973c4a609162c8b4247c5a93c9fb52a786ea8cccb4d4)
declare_datasource (FILE 16bins50overlap_reference_metadata.tsv
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/16bins50overlap_reference_metadata.tsv
                URL_HASH SHA256=8ed578817aadb6390957047dad4d16e952325e48824d0a7041f6e6a59414ac3d)
declare_datasource (FILE 50overlap_full.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/50overlap_full.gff
                URL_HASH SHA256=6a073b53e85d4e099dd3f875e1257fbccce866e5738763729818e6297c7cb4be)
declare_datasource (FILE 8bins10overlap_dream_all.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/8bins10overlap_dream_all.gff
                URL_HASH SHA256=3644af79d5732c2d0d515db6733e5c13d67d4b0840176ee0e0d4058b1d3eafff)
declare_datasource (FILE 8bins10overlap_dream_consolidated.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/8bins10overlap_dream_consolidated.gff
                URL_HASH SHA256=296b99ee23f03f859274b88f5f6ffe08ac15a41f419282bf2a608dfdbd0f6ac7)
declare_datasource (FILE 8bins10overlap_reference_metadata.tsv
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/8bins10overlap_reference_metadata.tsv
                URL_HASH SHA256=8ed578817aadb6390957047dad4d16e952325e48824d0a7041f6e6a59414ac3d)
declare_datasource (FILE 8bins50overlap_dream_all.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/8bins50overlap_dream_all.gff
                URL_HASH SHA256=b03c92c88ad507b5a48111538552dd29cd491dc1eb365e3db739c5a99b4e8409)
declare_datasource (FILE 8bins50overlap_dream_consolidated.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/8bins50overlap_dream_consolidated.gff
                URL_HASH SHA256=e436b20ab0b35bc0c9bf973c4a609162c8b4247c5a93c9fb52a786ea8cccb4d4)
declare_datasource (FILE 8bins50overlap_reference_metadata.tsv
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/8bins50overlap_reference_metadata.tsv
                URL_HASH SHA256=8ed578817aadb6390957047dad4d16e952325e48824d0a7041f6e6a59414ac3d)
declare_datasource (FILE multi_seq_ref.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/multi_seq_ref.fasta
                URL_HASH SHA256=24d5bf54edf054b7407a0bc4707b72383b9467c051839a6cbd8ec8e2b6bb65f9)
declare_datasource (FILE query_e0.05.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/query_e0.05.fasta
                URL_HASH SHA256=b107238db9e0c0515b33fff570a787a86126789a0341bd2fdb52c6c607772f8d)
