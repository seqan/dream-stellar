cmake_minimum_required (VERSION 3.16)

include (cmake/app_datasources.cmake)

declare_datasource (FILE database.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/split/database.fasta
                URL_HASH SHA256=7c7a8fcdd52a932cda76219f24024c1624292377103d9fd5a55abd288c6072be)
declare_datasource (FILE single_query.fq
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single_query.fq
                URL_HASH SHA256=6f6837a3313b8288a1cffa1091329cf797ef72e2501c13e2b7dbd285a63a193b)
declare_datasource (FILE single_reference.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single_reference.fasta
                URL_HASH SHA256=53d633474b01a68927d3ab1fd970b200e96403bb1fdcc53feb0367a2093be273)
declare_datasource (FILE various_chromosome_lengths.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/split/various_chromosome_lengths.fasta
                URL_HASH SHA256=7c7a8fcdd52a932cda76219f24024c1624292377103d9fd5a55abd288c6072be)


declare_datasource (FILE 150overlap16bins13window1errors.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap16bins13window1errors.gff.out
                URL_HASH SHA256=118f6f235b77ffe9fcf91067cbf718a2ca7d3ce0d3406b9f83a8238be603e155)
declare_datasource (FILE 150overlap16bins13window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap16bins13window.ibf
                URL_HASH SHA256=f774150b74f9c66f108b17bcccf8f7e7782c9940c6ad0faa8cc7910c4a397725)
declare_datasource (FILE 150overlap16bins15window1errors.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap16bins15window1errors.gff.out
                URL_HASH SHA256=118f6f235b77ffe9fcf91067cbf718a2ca7d3ce0d3406b9f83a8238be603e155)
declare_datasource (FILE 150overlap16bins15window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap16bins15window.ibf
                URL_HASH SHA256=fde51c6b696e5b0e1904fd20c9396385f0e1770beb24e9a6c63de57cdc9ae9e8)
declare_datasource (FILE 150overlap16bins.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap16bins.txt
                URL_HASH SHA256=c019d484423e2f39120992e0ef619326b8d7f6d9f46801f83f4cb676e2fd3361)
declare_datasource (FILE 150overlap4bins13window1errors.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap4bins13window1errors.gff.out
                URL_HASH SHA256=d45982f54310c2037e3b75da6cfff62179eff043d41e4987a575f0727415c4ea)
declare_datasource (FILE 150overlap4bins13window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap4bins13window.ibf
                URL_HASH SHA256=690c52011ba874eb76aee594a66cf682726a5332eaea76e4272d5f40dfe12865)
declare_datasource (FILE 150overlap4bins15window1errors.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap4bins15window1errors.gff.out
                URL_HASH SHA256=a12cad7ceae234ab1dd051d08e9a8463ab32793980ee42d383cf63fcf890405b)
declare_datasource (FILE 150overlap4bins15window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap4bins15window.ibf
                URL_HASH SHA256=f38d6f8c9bbeb9eaf55690e979a32517b7963673a8b23433308db8b92333bf4a)
declare_datasource (FILE 150overlap4bins.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap4bins.txt
                URL_HASH SHA256=07e7b628760e3d6d3df88f28006c2416ab079d6cb3c8c9032d1538209e3d7eff)


declare_datasource (FILE 0overlap16bins.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/multi/0overlap16bins.txt
                URL_HASH SHA256=981d9d686a99586d405d7939dcd758477c079c0e6779cd95829605f466d15baa)
declare_datasource (FILE 0overlap4bins.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/multi/0overlap4bins.txt
                URL_HASH SHA256=c769012bdccd3a918c6e47a1e9bc6f3988d085babc591bfa5461982156cd4188)
declare_datasource (FILE 20overlap16bins.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/multi/20overlap16bins.txt
                URL_HASH SHA256=995f3f151b97bedb9d596bfe41f17deb54f5bf53f5065defb45f9828956665fc)
declare_datasource (FILE 20overlap4bins.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/multi/20overlap4bins.txt
                URL_HASH SHA256=c769012bdccd3a918c6e47a1e9bc6f3988d085babc591bfa5461982156cd4188)


declare_datasource (FILE write_out_0_16_reference_metadata.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/write_out_0_16/reference_metadata.txt
                URL_HASH SHA256=981d9d686a99586d405d7939dcd758477c079c0e6779cd95829605f466d15baa)
declare_datasource (FILE write_out_0_4_reference_metadata.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/write_out_0_4/reference_metadata.txt
                URL_HASH SHA256=c769012bdccd3a918c6e47a1e9bc6f3988d085babc591bfa5461982156cd4188)
declare_datasource (FILE write_out_20_16_reference_metadata.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/write_out_20_16/reference_metadata.txt
                URL_HASH SHA256=995f3f151b97bedb9d596bfe41f17deb54f5bf53f5065defb45f9828956665fc)
declare_datasource (FILE write_out_20_4_reference_metadata.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/write_out_20_4/reference_metadata.txt
                URL_HASH SHA256=c769012bdccd3a918c6e47a1e9bc6f3988d085babc591bfa5461982156cd4188)
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
declare_datasource (FILE in.test
                URL ${CMAKE_SOURCE_DIR}/test/data/build/in.test
                URL_HASH SHA256=3a13c890650bf857770816244ed9420295ad8bbe681dac335f687863fc79a603)
declare_datasource (FILE query.fa
                URL ${CMAKE_SOURCE_DIR}/test/data/build/query.fa
                URL_HASH SHA256=a9f146ff2223cdd339f6900bef20aee73bcbccce8336910238a469425908bbd8)
declare_datasource (FILE search.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/build/search.gff
                URL_HASH SHA256=2444cde721603ea886cf2d17b6d7726844278c3fbd19ba3759794434cd6b1e31)
declare_datasource (FILE search.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/build/search.gff.out
                URL_HASH SHA256=26679f873197106e9a37ee8178555f9d4c49882e7d7c51accd446fe524dcf5d1)
declare_datasource (FILE test.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/build/test.gff.out
                URL_HASH SHA256=c4aa4f0cd84a190b1ba2abd675cd2f619c4920bf0f5b58364b5b6dc485eddaa2)


declare_datasource (FILE 8bins19window0error100pattern1overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error100pattern1overlap.gff.out
                URL_HASH SHA256=e5195e7e9aa2db1864fbefc987d836abf68c019ba974b5b56fff1d8d7acaf780)
declare_datasource (FILE 8bins19window0error100pattern40overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error100pattern40overlap.gff.out
                URL_HASH SHA256=e5195e7e9aa2db1864fbefc987d836abf68c019ba974b5b56fff1d8d7acaf780)
declare_datasource (FILE 8bins19window0error50pattern1overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error50pattern1overlap.gff.out
                URL_HASH SHA256=370442879ed07dbd6a5cb358695b8f8118803cee7c4bbd0dea6ebb17499f968f)
declare_datasource (FILE 8bins19window0error50pattern40overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error50pattern40overlap.gff.out
                URL_HASH SHA256=370442879ed07dbd6a5cb358695b8f8118803cee7c4bbd0dea6ebb17499f968f)
declare_datasource (FILE 8bins19window1error100pattern1overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error100pattern1overlap.gff.out
                URL_HASH SHA256=850fdb8afa39409fb91ff552a7c5c4e8efafbf7305accfb87afe1366dbd234b4)
declare_datasource (FILE 8bins19window1error100pattern40overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error100pattern40overlap.gff.out
                URL_HASH SHA256=5e6059b76815b454926439a477cbb1e48a3e611a75c50bd5421aae258a9888b0)
declare_datasource (FILE 8bins19window1error50pattern1overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error50pattern1overlap.gff.out
                URL_HASH SHA256=3b8ab3cf3ddd8bde12610265053b6e388008548a684d3ce9ffe86cc0aded9dd0)
declare_datasource (FILE 8bins19window1error50pattern40overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error50pattern40overlap.gff.out
                URL_HASH SHA256=e87d9177c94fe52fb156dd09ff7d074dc88672d36e25ef625a08800fa94525a2)
declare_datasource (FILE 8bins23window0error100pattern1overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error100pattern1overlap.gff.out
                URL_HASH SHA256=e5195e7e9aa2db1864fbefc987d836abf68c019ba974b5b56fff1d8d7acaf780)
declare_datasource (FILE 8bins23window0error100pattern40overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error100pattern40overlap.gff.out
                URL_HASH SHA256=e5195e7e9aa2db1864fbefc987d836abf68c019ba974b5b56fff1d8d7acaf780)
declare_datasource (FILE 8bins23window0error50pattern1overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error50pattern1overlap.gff.out
                URL_HASH SHA256=370442879ed07dbd6a5cb358695b8f8118803cee7c4bbd0dea6ebb17499f968f)
declare_datasource (FILE 8bins23window0error50pattern40overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error50pattern40overlap.gff.out
                URL_HASH SHA256=370442879ed07dbd6a5cb358695b8f8118803cee7c4bbd0dea6ebb17499f968f)
declare_datasource (FILE 8bins23window1error100pattern1overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error100pattern1overlap.gff.out
                URL_HASH SHA256=921225eae9d8e54963d2423e39ee349158a2e39fc52c8926707749bcda1163a4)
declare_datasource (FILE 8bins23window1error100pattern40overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error100pattern40overlap.gff.out
                URL_HASH SHA256=583d848d9c2e5c082404283f0f4fa04ff55e99a2ee50418c4ced6f7673fbaa9e)
declare_datasource (FILE 8bins23window1error50pattern1overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error50pattern1overlap.gff.out
                URL_HASH SHA256=3b8ab3cf3ddd8bde12610265053b6e388008548a684d3ce9ffe86cc0aded9dd0)
declare_datasource (FILE 8bins23window1error50pattern40overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error50pattern40overlap.gff.out
                URL_HASH SHA256=25f679f1387c823db111913dc25b6c7a0c81ad7b07b1296e37e6acc6e19b9cac)
declare_datasource (FILE query.fq
                URL ${CMAKE_SOURCE_DIR}/test/data/search/query.fq
                URL_HASH SHA256=65fbd58c14ca2b4c2274f44fff14dbfce54dc04a89cf6759e1a69cecba933130)


declare_datasource (FILE 16bins50overlap_dream_all.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/16bins50overlap_dream_all.gff
                URL_HASH SHA256=3ecd0e55e704cfd71442bd16805fe587de720e646cbe2d13675ed6249b30045f)
declare_datasource (FILE 16bins50overlap_reference_metadata.tsv
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/16bins50overlap_reference_metadata.tsv
                URL_HASH SHA256=296b7020ec5cdd78d75464dcaec82cbced9a32a22a92b857792a2a01e67effa0)
declare_datasource (FILE 8bins50overlap_dream_all.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/8bins50overlap_dream_all.gff
                URL_HASH SHA256=f03c93ddb758a7e9ef89e3243dca9fb49b97a1ba3239408ffc30f8ff486982c8)
declare_datasource (FILE 8bins50overlap_reference_metadata.tsv
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/8bins50overlap_reference_metadata.tsv
                URL_HASH SHA256=22ff51c797d739ebb2c12332ca7067550e191c2c5fe75ad54cb680f38e423eb5)
declare_datasource (FILE multi_seq_query.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/multi_seq_query.fasta
                URL_HASH SHA256=6d1260dc701802924487453c19715044cbeaa0f42021be8f2996bbaac1f24c58)
declare_datasource (FILE multi_seq_ref.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/multi_seq_ref.fasta
                URL_HASH SHA256=a37f4be29ec99b66efb6ac235224b3145aadf8d5d6ff2c5c2f5324890170ce92)
declare_datasource (FILE stellar_truth_disable10_num3.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/stellar_truth_disable10_num3.gff
                URL_HASH SHA256=3b042d2ce697bcdb39adfc65c0964139234260ca0cc7bc84afa4f20675d2bc46)
declare_datasource (FILE stellar_truth_disable10_num5.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/stellar_truth_disable10_num5.gff
                URL_HASH SHA256=d52e734519b704c7feab24d2ce7e82f0559c09b0838b0195777c767a7b5595b4)
declare_datasource (FILE stellar_truth_disable10_num9.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/stellar_truth_disable10_num9.gff
                URL_HASH SHA256=41c5bcbee5482ffb74be71d5a955762d7cc65e59a9ca63fda3a71264775d7b7d)
declare_datasource (FILE stellar_truth_disable12_num3.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/stellar_truth_disable12_num3.gff
                URL_HASH SHA256=315f57cedc484dcf074c4d8f0c199d73480fe0d9d5a58e5072df28c8e7d1694f)
declare_datasource (FILE stellar_truth_disable12_num5.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/stellar_truth_disable12_num5.gff
                URL_HASH SHA256=a5ab9ae23bfba6a204019f35a61bbf380bec2136179356609bf7194ca879ed3b)
declare_datasource (FILE stellar_truth_disable12_num9.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/stellar_truth_disable12_num9.gff
                URL_HASH SHA256=95bf8d1fcbcfde4dfea3cd2055bcf35be161e6b21519e2c936b3595ef37c017b)
declare_datasource (FILE stellar_truth_disable7_num3.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/stellar_truth_disable7_num3.gff
                URL_HASH SHA256=2afec8a11ed6219ddabd348c194782155bac669b84c4235ca31a3dca2cd12446)
declare_datasource (FILE stellar_truth_disable7_num5.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/stellar_truth_disable7_num5.gff
                URL_HASH SHA256=4de9fbed546431321a654c10cd87b5c78df2f690f2fd8817ab3da282bb608206)
declare_datasource (FILE stellar_truth_disable7_num9.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/stellar_truth_disable7_num9.gff
                URL_HASH SHA256=5d86fe14ccb3b07bb20000ae591da2d9151df40c8e41f2563f660a8df45ef453)
declare_datasource (FILE stellar_truth_disable9_num3.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/stellar_truth_disable9_num3.gff
                URL_HASH SHA256=a9a4b6257c4f400fb2c3115dc8e5d7c472e54473ad3f750fc03cfe64b6683b17)
declare_datasource (FILE stellar_truth_disable9_num5.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/stellar_truth_disable9_num5.gff
                URL_HASH SHA256=0ed76eacec07ee91caa6f4c9dd437f5cca909393209edc5504f7bfab77c5e4d7)
declare_datasource (FILE stellar_truth_disable9_num9.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/stellar_truth_disable9_num9.gff
                URL_HASH SHA256=bf933d08db2db066c4bf29b85f4fe579631f7c6d30c413ecfb515a42936e839b)
declare_datasource (FILE stellar_truth.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/stellar_truth.gff
                URL_HASH SHA256=95bf8d1fcbcfde4dfea3cd2055bcf35be161e6b21519e2c936b3595ef37c017b)


declare_datasource (FILE 16bins13window1error.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/16bins13window1error.gff
                URL_HASH SHA256=cea1404068b636ea0e9d8be24c53612126fc2ee6fa88f3fd277c7aeeca3109fc)
declare_datasource (FILE 16bins13window1error.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/16bins13window1error.gff.out
                URL_HASH SHA256=e2970f75dc39643d3079e92b75603a33348548eeaa055fdb08db41debaa4565b)
declare_datasource (FILE 16bins15window1error.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/16bins15window1error.gff
                URL_HASH SHA256=cea1404068b636ea0e9d8be24c53612126fc2ee6fa88f3fd277c7aeeca3109fc)
declare_datasource (FILE 16bins15window1error.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/16bins15window1error.gff.out
                URL_HASH SHA256=fe956ec2e331b12106ab67d338cd8bf57b7495604b2fc8a90d1111d1675aa1b7)
declare_datasource (FILE 4bins13window1error.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/4bins13window1error.gff
                URL_HASH SHA256=cea1404068b636ea0e9d8be24c53612126fc2ee6fa88f3fd277c7aeeca3109fc)
declare_datasource (FILE 4bins13window1error.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/4bins13window1error.gff.out
                URL_HASH SHA256=73451c6286a314bfc77fe95038a4d9138aa3b19d4d5f2dfa8d54a238110e7110)
declare_datasource (FILE 4bins15window1error.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/4bins15window1error.gff
                URL_HASH SHA256=cea1404068b636ea0e9d8be24c53612126fc2ee6fa88f3fd277c7aeeca3109fc)
declare_datasource (FILE 4bins15window1error.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/4bins15window1error.gff.out
                URL_HASH SHA256=73451c6286a314bfc77fe95038a4d9138aa3b19d4d5f2dfa8d54a238110e7110)
declare_datasource (FILE dummy_reads.fastq
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/dummy_reads.fastq
                URL_HASH SHA256=f1aa9ca0fb0b87393923848f0389cc3fb5cfd4841566afaf72e6c55829b64d73)
declare_datasource (FILE query.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/query.fasta
                URL_HASH SHA256=75e292d38ed610518baab4f4b07c8c3b50195da0e10be4f5a08e8717d9ed90b9)
declare_datasource (FILE query.fastq
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/query.fastq
                URL_HASH SHA256=5595795b4d31b98b64dc9f2b54953eb6f76bc59fd14a3d94e84a4444a90912c8)
declare_datasource (FILE query_meta.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/query_meta.txt
                URL_HASH SHA256=1eb7e99026c694bddfdd61125084264d1b2a526a174aae5c8422c418a29ad9f0)
declare_datasource (FILE query_seg_meta.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/query_seg_meta.txt
                URL_HASH SHA256=4eea1ab7f93165dbfec9baa509a9b4d2e4deda0047da79ebcc55a5c7b2982dac)
declare_datasource (FILE ref.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/ref.fasta
                URL_HASH SHA256=47f808d207c4c90afebbe1c8ab28990ec0e3e777c75ec787099279005428f3da)
declare_datasource (FILE ref_meta.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/ref_meta.txt
                URL_HASH SHA256=cfaea330c4abde12e75cec5ae8b74ffd985d2b1d4ad1620b72e064f17488e1d5)
declare_datasource (FILE seg_meta150overlap16bins.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/seg_meta150overlap16bins.txt
                URL_HASH SHA256=fae21b4e8f3ac79d6afe30392a33c906bc6d13cfce453306fb691bc85f903379)
declare_datasource (FILE seg_meta150overlap4bins.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/seg_meta150overlap4bins.txt
                URL_HASH SHA256=fb54ed4ec95d134f07e78ad3fd348e379d95fa11f29e5215dd76d509211ff324)
declare_datasource (FILE stellar.disabled.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/stellar.disabled.fasta
                URL_HASH SHA256=ec82b20c625078444055d0d5d74c0a85b91d19ad79e54f500fe5af2e4fe5b344)
