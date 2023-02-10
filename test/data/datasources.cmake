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


declare_datasource (FILE 150overlap16bins13window1errors.out
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap16bins13window1errors.out
                URL_HASH SHA256=cbdbcfc5d010e57883773c7a42024fc4ad392dc99da1488b0c33b6dd39a477a9)
declare_datasource (FILE 150overlap16bins13window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap16bins13window.ibf
                URL_HASH SHA256=bf2db42adc669ab73b074d74758ad56cf35d0c396031a0e73809b659fe8a76ce)
declare_datasource (FILE 150overlap16bins15window1errors.out
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap16bins15window1errors.out
                URL_HASH SHA256=cbdbcfc5d010e57883773c7a42024fc4ad392dc99da1488b0c33b6dd39a477a9)
declare_datasource (FILE 150overlap16bins15window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap16bins15window.ibf
                URL_HASH SHA256=cb18705eaa1a94963969e7381efc3b5c099c241d7446a7292203c5d5b434b127)
declare_datasource (FILE 150overlap16bins.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap16bins.txt
                URL_HASH SHA256=39501216962a5103aad09575248167cf5cfa63c96598ea8fcd7134421e1c8504)
declare_datasource (FILE 150overlap4bins13window1errors.out
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap4bins13window1errors.out
                URL_HASH SHA256=0492c71fbf415f5356801e62382e3d3e8ba101d513798f599dc1b04a9432c45f)
declare_datasource (FILE 150overlap4bins13window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap4bins13window.ibf
                URL_HASH SHA256=ce7b31acef135e024af9268b3416030d85e4c2828bc8c5dc3d1f18a34a03d373)
declare_datasource (FILE 150overlap4bins15window1errors.out
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap4bins15window1errors.out
                URL_HASH SHA256=a5c7f5714cd25417777a9aaef55842d60e13266354db8f5595f2bc82c62a21c3)
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


declare_datasource (FILE 8bins19window0error100pattern1overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error100pattern1overlap.out
                URL_HASH SHA256=88711f9e06e387a00d8ce4e3a0579889f9a9fb2d96fe2daf685994d376094bd5)
declare_datasource (FILE 8bins19window0error100pattern40overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error100pattern40overlap.out
                URL_HASH SHA256=88711f9e06e387a00d8ce4e3a0579889f9a9fb2d96fe2daf685994d376094bd5)
declare_datasource (FILE 8bins19window0error50pattern1overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error50pattern1overlap.out
                URL_HASH SHA256=4c74f3d66f57c77eefa1ca2fdf98bc00c23cac50a608ac834085c5d80fb59bb2)
declare_datasource (FILE 8bins19window0error50pattern40overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error50pattern40overlap.out
                URL_HASH SHA256=4c74f3d66f57c77eefa1ca2fdf98bc00c23cac50a608ac834085c5d80fb59bb2)
declare_datasource (FILE 8bins19window1error100pattern1overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error100pattern1overlap.out
                URL_HASH SHA256=10b13e95329dbe9ee44471d8bd03c4c191096a0408d5603633817959616e496c)
declare_datasource (FILE 8bins19window1error100pattern40overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error100pattern40overlap.out
                URL_HASH SHA256=10b13e95329dbe9ee44471d8bd03c4c191096a0408d5603633817959616e496c)
declare_datasource (FILE 8bins19window1error50pattern1overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error50pattern1overlap.out
                URL_HASH SHA256=57525d249d608a81419e58fecd86cbe441e28d56dc562ee19b94dd42093da607)
declare_datasource (FILE 8bins19window1error50pattern40overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error50pattern40overlap.out
                URL_HASH SHA256=93f7d77006afcdb4ae671505444be362762c7eda3ff18f0a099bb4f7229b3c6c)
declare_datasource (FILE 8bins23window0error100pattern1overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error100pattern1overlap.out
                URL_HASH SHA256=88711f9e06e387a00d8ce4e3a0579889f9a9fb2d96fe2daf685994d376094bd5)
declare_datasource (FILE 8bins23window0error100pattern40overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error100pattern40overlap.out
                URL_HASH SHA256=88711f9e06e387a00d8ce4e3a0579889f9a9fb2d96fe2daf685994d376094bd5)
declare_datasource (FILE 8bins23window0error50pattern1overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error50pattern1overlap.out
                URL_HASH SHA256=4c74f3d66f57c77eefa1ca2fdf98bc00c23cac50a608ac834085c5d80fb59bb2)
declare_datasource (FILE 8bins23window0error50pattern40overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error50pattern40overlap.out
                URL_HASH SHA256=4c74f3d66f57c77eefa1ca2fdf98bc00c23cac50a608ac834085c5d80fb59bb2)
declare_datasource (FILE 8bins23window1error100pattern1overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error100pattern1overlap.out
                URL_HASH SHA256=3b786c19b3db74dc8b40a61da5f339892a893d0e3cb3b843fc4d931bbf9f9dd3)
declare_datasource (FILE 8bins23window1error100pattern40overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error100pattern40overlap.out
                URL_HASH SHA256=3b786c19b3db74dc8b40a61da5f339892a893d0e3cb3b843fc4d931bbf9f9dd3)
declare_datasource (FILE 8bins23window1error50pattern1overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error50pattern1overlap.out
                URL_HASH SHA256=d2652d22b9249588b380c0b7a7a1ef004cc2b3a132c8d3451ab98a30520ebd10)
declare_datasource (FILE 8bins23window1error50pattern40overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error50pattern40overlap.out
                URL_HASH SHA256=48179da0562cb6b7b3664a49176b5f07057b8107143f6506a8faa799548c9a0f)
declare_datasource (FILE query.fq
                URL ${CMAKE_SOURCE_DIR}/test/data/search/query.fq
                URL_HASH SHA256=4d684a7e4f8b2a9eceb927edaf1a17543c6bbab7efa6a5eedfeb90465caa37ed)


declare_datasource (FILE 10overlap_full.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/10overlap_full.gff
                URL_HASH SHA256=b9043f11a9dedb52123a8573f965b140e3fa5683de5471a93818240421bd44a8)
declare_datasource (FILE 16bins10overlap_dream_all.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/16bins10overlap_dream_all.gff
                URL_HASH SHA256=1ea90736d2ea59bc9933f75807fa033756823bd663a2e93d5cd7fb7a959ca1c7)
declare_datasource (FILE 16bins10overlap_dream_consolidated.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/16bins10overlap_dream_consolidated.gff
                URL_HASH SHA256=296b99ee23f03f859274b88f5f6ffe08ac15a41f419282bf2a608dfdbd0f6ac7)
declare_datasource (FILE 16bins10overlap_reference_metadata.tsv
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/16bins10overlap_reference_metadata.tsv
                URL_HASH SHA256=8ed578817aadb6390957047dad4d16e952325e48824d0a7041f6e6a59414ac3d)
declare_datasource (FILE 16bins50overlap_dream_all.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/16bins50overlap_dream_all.gff
                URL_HASH SHA256=bcd8ada8c90e04008b3df9df00859f205550a1a4b0f0f1c2e4a46388fec8e97c)
declare_datasource (FILE 16bins50overlap_dream_consolidated.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/16bins50overlap_dream_consolidated.gff
                URL_HASH SHA256=e436b20ab0b35bc0c9bf973c4a609162c8b4247c5a93c9fb52a786ea8cccb4d4)
declare_datasource (FILE 16bins50overlap_reference_metadata.tsv
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/16bins50overlap_reference_metadata.tsv
                URL_HASH SHA256=8ed578817aadb6390957047dad4d16e952325e48824d0a7041f6e6a59414ac3d)
declare_datasource (FILE 50overlap_full.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/50overlap_full.gff
                URL_HASH SHA256=7b4524e5bece4fbb2269e169d46d5e9c728e60452748f6f9b63c8886186056fe)
declare_datasource (FILE 8bins10overlap_dream_all.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/8bins10overlap_dream_all.gff
                URL_HASH SHA256=0d104b2c3943ace7cac9c987c1e1aa8a3744b04c04148efe94dfa4f2a7f35c13)
declare_datasource (FILE 8bins10overlap_dream_consolidated.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/8bins10overlap_dream_consolidated.gff
                URL_HASH SHA256=296b99ee23f03f859274b88f5f6ffe08ac15a41f419282bf2a608dfdbd0f6ac7)
declare_datasource (FILE 8bins10overlap_reference_metadata.tsv
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/8bins10overlap_reference_metadata.tsv
                URL_HASH SHA256=8ed578817aadb6390957047dad4d16e952325e48824d0a7041f6e6a59414ac3d)
declare_datasource (FILE 8bins50overlap_dream_all.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/8bins50overlap_dream_all.gff
                URL_HASH SHA256=0c6f48c11cc165210a401952e3b6d040169dcdfd0449a55a228f588c11681b60)
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
