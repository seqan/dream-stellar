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


declare_datasource (FILE 150overlap16bins13window1errors.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap16bins13window1errors.gff.out
                URL_HASH SHA256=385348354ed4cf421e498d0606e4ac45c31fe617e9f6b8a8b1ac7b420f248c9e)
declare_datasource (FILE 150overlap16bins13window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap16bins13window.ibf
                URL_HASH SHA256=bf2db42adc669ab73b074d74758ad56cf35d0c396031a0e73809b659fe8a76ce)
declare_datasource (FILE 150overlap16bins15window1errors.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap16bins15window1errors.gff.out
                URL_HASH SHA256=385348354ed4cf421e498d0606e4ac45c31fe617e9f6b8a8b1ac7b420f248c9e)
declare_datasource (FILE 150overlap16bins15window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap16bins15window.ibf
                URL_HASH SHA256=cb18705eaa1a94963969e7381efc3b5c099c241d7446a7292203c5d5b434b127)
declare_datasource (FILE 150overlap16bins.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap16bins.txt
                URL_HASH SHA256=39501216962a5103aad09575248167cf5cfa63c96598ea8fcd7134421e1c8504)
declare_datasource (FILE 150overlap4bins13window1errors.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap4bins13window1errors.gff.out
                URL_HASH SHA256=cf089fdd11b2b5078a838f07cc9350eb0261361e4379bbbcd17be7f65765b3ec)
declare_datasource (FILE 150overlap4bins13window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap4bins13window.ibf
                URL_HASH SHA256=ce7b31acef135e024af9268b3416030d85e4c2828bc8c5dc3d1f18a34a03d373)
declare_datasource (FILE 150overlap4bins15window1errors.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap4bins15window1errors.gff.out
                URL_HASH SHA256=fa07ea953b294982661f3fe772e71e192b89245e0559445b15bdd6d1da4dccf0)
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


declare_datasource (FILE 8bins19window0error100pattern1overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error100pattern1overlap.gff.out
                URL_HASH SHA256=cfeb2fdc80371ede98bff6b1b25e0eedf19866b9d545bdfd6e9b068dbbf3f7d5)
declare_datasource (FILE 8bins19window0error100pattern40overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error100pattern40overlap.gff.out
                URL_HASH SHA256=3c8232f56bb5b48a2c4e8d41dfe377b825e1fb414713505b21ea3501c6ab3f21)
declare_datasource (FILE 8bins19window0error50pattern1overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error50pattern1overlap.gff.out
                URL_HASH SHA256=264c32fe0efb1ec10b4e3b590d2aa34411d78a97effb190d550f87ee6c4e7071)
declare_datasource (FILE 8bins19window0error50pattern40overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error50pattern40overlap.gff.out
                URL_HASH SHA256=83516e71a8c944c1fd53d9b009546ea9492bd8b9de3481ce4d5219563958f158)
declare_datasource (FILE 8bins19window1error100pattern1overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error100pattern1overlap.gff.out
                URL_HASH SHA256=a7c03bd84745bf7a63196d48d0fd398832a1f268702fe789d8cdab2a705f6832)
declare_datasource (FILE 8bins19window1error100pattern40overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error100pattern40overlap.gff.out
                URL_HASH SHA256=a7c03bd84745bf7a63196d48d0fd398832a1f268702fe789d8cdab2a705f6832)
declare_datasource (FILE 8bins19window1error50pattern1overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error50pattern1overlap.gff.out
                URL_HASH SHA256=ba8d8b30eb72c3849764925f42ac16fa3c885e8fada33ad21d6cc16053f7b0c6)
declare_datasource (FILE 8bins19window1error50pattern40overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error50pattern40overlap.gff.out
                URL_HASH SHA256=23b74eeb07a104fc7b8667ed0c2aa660b9b3d6d1af319870ea585b6bd93b2c94)
declare_datasource (FILE 8bins23window0error100pattern1overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error100pattern1overlap.gff.out
                URL_HASH SHA256=cfeb2fdc80371ede98bff6b1b25e0eedf19866b9d545bdfd6e9b068dbbf3f7d5)
declare_datasource (FILE 8bins23window0error100pattern40overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error100pattern40overlap.gff.out
                URL_HASH SHA256=cfeb2fdc80371ede98bff6b1b25e0eedf19866b9d545bdfd6e9b068dbbf3f7d5)
declare_datasource (FILE 8bins23window0error50pattern1overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error50pattern1overlap.gff.out
                URL_HASH SHA256=672a78cbf55b92f2b8ec3059a40094a414cce9b5512004e7371b3f3b7278c596)
declare_datasource (FILE 8bins23window0error50pattern40overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error50pattern40overlap.gff.out
                URL_HASH SHA256=39540f147051fe44efac841f1d111a3c9c882c606a7ff6f09e433a999c8fc12e)
declare_datasource (FILE 8bins23window1error100pattern1overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error100pattern1overlap.gff.out
                URL_HASH SHA256=cb7678c4d77278b1419f12cfb6c66ae5b9a568aa6d17d0ada35f40d566626365)
declare_datasource (FILE 8bins23window1error100pattern40overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error100pattern40overlap.gff.out
                URL_HASH SHA256=dbee5b94472d5efacb89e5947b84c9a443f2a189cddf5055e659d857c7ad41c3)
declare_datasource (FILE 8bins23window1error50pattern1overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error50pattern1overlap.gff.out
                URL_HASH SHA256=0f32d21fb620346511a3e57d54ddf2d1bbefbd797be85a99250d14b5b13c5b4f)
declare_datasource (FILE 8bins23window1error50pattern40overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error50pattern40overlap.gff.out
                URL_HASH SHA256=15dafc62819955efed07a1d3880ea7a78ff4464c247de6abc10cd925f58161c2)
declare_datasource (FILE query.fq
                URL ${CMAKE_SOURCE_DIR}/test/data/search/query.fq
                URL_HASH SHA256=4d684a7e4f8b2a9eceb927edaf1a17543c6bbab7efa6a5eedfeb90465caa37ed)


declare_datasource (FILE 16bins50overlap_dream_all.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/16bins50overlap_dream_all.gff
                URL_HASH SHA256=561dcb59d1499603e9ecbc4e5568fdec2cad30576c1c2fa4a6813776249bcf21)
declare_datasource (FILE 16bins50overlap_dream_all.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/16bins50overlap_dream_all.gff.out
                URL_HASH SHA256=7766aff53bfc03ffbfd09547b0950d081891bdb50bbcc4f5ad11a05fa9c86cfb)
declare_datasource (FILE 16bins50overlap_dream_consolidated.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/16bins50overlap_dream_consolidated.gff
                URL_HASH SHA256=96d8f859888fa875da2544aba8d95ac6598c543a0cabd52685899ea87a48d357)
declare_datasource (FILE 16bins50overlap_reference_metadata.tsv
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/16bins50overlap_reference_metadata.tsv
                URL_HASH SHA256=8ed578817aadb6390957047dad4d16e952325e48824d0a7041f6e6a59414ac3d)
declare_datasource (FILE 50overlap_full.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/50overlap_full.gff
                URL_HASH SHA256=45be895caedf69070e3433b5b912f7a20e2ac8ffe227e762fb33e5b31d43106a)
declare_datasource (FILE 8bins50overlap_dream_all.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/8bins50overlap_dream_all.gff
                URL_HASH SHA256=a3e819706188e76fa6478fc1314fe749661c1dc2f16de6f85ab737817e04e0b6)
declare_datasource (FILE 8bins50overlap_dream_all.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/8bins50overlap_dream_all.gff.out
                URL_HASH SHA256=41f391bf835537d98a0803dde12c2935c2ca8dbc0fb628a2e976f55474d0e331)
declare_datasource (FILE 8bins50overlap_dream_consolidated.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/8bins50overlap_dream_consolidated.gff
                URL_HASH SHA256=96d8f859888fa875da2544aba8d95ac6598c543a0cabd52685899ea87a48d357)
declare_datasource (FILE 8bins50overlap_reference_metadata.tsv
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/8bins50overlap_reference_metadata.tsv
                URL_HASH SHA256=8ed578817aadb6390957047dad4d16e952325e48824d0a7041f6e6a59414ac3d)
declare_datasource (FILE multi_seq_ref.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/multi_seq_ref.fasta
                URL_HASH SHA256=24d5bf54edf054b7407a0bc4707b72383b9467c051839a6cbd8ec8e2b6bb65f9)
declare_datasource (FILE query_e0.06.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/query_e0.06.fasta
                URL_HASH SHA256=b107238db9e0c0515b33fff570a787a86126789a0341bd2fdb52c6c607772f8d)
