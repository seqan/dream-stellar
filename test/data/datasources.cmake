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
                URL_HASH SHA256=fcce777123b91539b15c9ee75c8ae1aadb4f5e7228e327a1f3977466d0d7b48d)
declare_datasource (FILE 150overlap16bins13window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap16bins13window.ibf
                URL_HASH SHA256=f774150b74f9c66f108b17bcccf8f7e7782c9940c6ad0faa8cc7910c4a397725)
declare_datasource (FILE 150overlap16bins15window1errors.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap16bins15window1errors.gff.out
                URL_HASH SHA256=fcce777123b91539b15c9ee75c8ae1aadb4f5e7228e327a1f3977466d0d7b48d)
declare_datasource (FILE 150overlap16bins15window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap16bins15window.ibf
                URL_HASH SHA256=fde51c6b696e5b0e1904fd20c9396385f0e1770beb24e9a6c63de57cdc9ae9e8)
declare_datasource (FILE 150overlap16bins.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap16bins.txt
                URL_HASH SHA256=c019d484423e2f39120992e0ef619326b8d7f6d9f46801f83f4cb676e2fd3361)
declare_datasource (FILE 150overlap4bins13window1errors.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap4bins13window1errors.gff.out
                URL_HASH SHA256=c174570c8113a15b2b1b8857f80796cc3a9f91026de4714205b949fc16427667)
declare_datasource (FILE 150overlap4bins13window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap4bins13window.ibf
                URL_HASH SHA256=690c52011ba874eb76aee594a66cf682726a5332eaea76e4272d5f40dfe12865)
declare_datasource (FILE 150overlap4bins15window1errors.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/150overlap4bins15window1errors.gff.out
                URL_HASH SHA256=ce9075e07dc743ca489b9bd7e931a4c38e29b7225f4c0163d0be852c801f28e1)
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


declare_datasource (FILE 8bins19window0error100pattern1overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error100pattern1overlap.gff.out
                URL_HASH SHA256=7f9e5b93543ce68170401e9c232f06163ac03572b3bab5a4832e454ca6798f7d)
declare_datasource (FILE 8bins19window0error100pattern40overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error100pattern40overlap.gff.out
                URL_HASH SHA256=c295444648d03f1c1026097eff7fe2208cac4b9df10994c1c8d3bd5f9c88c000)
declare_datasource (FILE 8bins19window0error50pattern1overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error50pattern1overlap.gff.out
                URL_HASH SHA256=f0da1e61168366464be902ff1bc98a7523d05fb5d9bef46fcd77014cc830c15e)
declare_datasource (FILE 8bins19window0error50pattern40overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error50pattern40overlap.gff.out
                URL_HASH SHA256=2676dc29e99f9438461444375147badd6b61aa2590dd69c1517c76538e149b67)
declare_datasource (FILE 8bins19window1error100pattern1overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error100pattern1overlap.gff.out
                URL_HASH SHA256=15eda389169bfe923e8a762f1622ac64165aaeb4d26e0b726dadeb267632d3aa)
declare_datasource (FILE 8bins19window1error100pattern40overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error100pattern40overlap.gff.out
                URL_HASH SHA256=581ccde0e976cea34fdb09fd3ef75c19072ffeae2430483eb12842748b1dc693)
declare_datasource (FILE 8bins19window1error50pattern1overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error50pattern1overlap.gff.out
                URL_HASH SHA256=331e01cb1d27c5e519c83bb4a3da802797865b7a922920980b364891712f21c7)
declare_datasource (FILE 8bins19window1error50pattern40overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error50pattern40overlap.gff.out
                URL_HASH SHA256=3e2c48729abe96e4ae54ddfe4c28e79832f729b4904dcd7b543b750fc2f20751)
declare_datasource (FILE 8bins23window0error100pattern1overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error100pattern1overlap.gff.out
                URL_HASH SHA256=c295444648d03f1c1026097eff7fe2208cac4b9df10994c1c8d3bd5f9c88c000)
declare_datasource (FILE 8bins23window0error100pattern40overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error100pattern40overlap.gff.out
                URL_HASH SHA256=c295444648d03f1c1026097eff7fe2208cac4b9df10994c1c8d3bd5f9c88c000)
declare_datasource (FILE 8bins23window0error50pattern1overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error50pattern1overlap.gff.out
                URL_HASH SHA256=ace528bfab58cb03d57ccc50d0b6384b5144fbf9e1bd1435085444ebfcfd188f)
declare_datasource (FILE 8bins23window0error50pattern40overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error50pattern40overlap.gff.out
                URL_HASH SHA256=ace528bfab58cb03d57ccc50d0b6384b5144fbf9e1bd1435085444ebfcfd188f)
declare_datasource (FILE 8bins23window1error100pattern1overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error100pattern1overlap.gff.out
                URL_HASH SHA256=747615386524195a703ed1bf33f718e49a9d4e22dd8bddac3cf4ca3b15f4e561)
declare_datasource (FILE 8bins23window1error100pattern40overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error100pattern40overlap.gff.out
                URL_HASH SHA256=747615386524195a703ed1bf33f718e49a9d4e22dd8bddac3cf4ca3b15f4e561)
declare_datasource (FILE 8bins23window1error50pattern1overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error50pattern1overlap.gff.out
                URL_HASH SHA256=74d26fb72098e0ceac69a19a6b54814c757d5250c09d4efd9347d95407698b7e)
declare_datasource (FILE 8bins23window1error50pattern40overlap.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error50pattern40overlap.gff.out
                URL_HASH SHA256=c684b863d861cfe3f28e40d17cf0a8051114212114ca08ee92c06619be1719d8)
declare_datasource (FILE query.fq
                URL ${CMAKE_SOURCE_DIR}/test/data/search/query.fq
                URL_HASH SHA256=65fbd58c14ca2b4c2274f44fff14dbfce54dc04a89cf6759e1a69cecba933130)


declare_datasource (FILE 16bins50overlap_dream_all.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/16bins50overlap_dream_all.gff
                URL_HASH SHA256=c03c2d8be51205313e42ed39fb3c17d4c8e74a47d95fd48d66a375f80901f11f)
declare_datasource (FILE 16bins50overlap_reference_metadata.tsv
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/16bins50overlap_reference_metadata.tsv
                URL_HASH SHA256=6be46e1b07e399ee5e6db355cfe92ccd1692354b873a80cb1f024473dac722d7)
declare_datasource (FILE 8bins50overlap_dream_all.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/8bins50overlap_dream_all.gff
                URL_HASH SHA256=0cd79ced4d2e6437459bb45b6571420351bcbc5ab8e8608e13d9b293e43f5c6f)
declare_datasource (FILE 8bins50overlap_reference_metadata.tsv
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/8bins50overlap_reference_metadata.tsv
                URL_HASH SHA256=055917899564e1f3c9f0d5efdb3b8599d075faa88231737f851bf6a1166651ef)
declare_datasource (FILE multi_seq_ref.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/multi_seq_ref.fasta
                URL_HASH SHA256=24d5bf54edf054b7407a0bc4707b72383b9467c051839a6cbd8ec8e2b6bb65f9)
declare_datasource (FILE query_e0.06.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/query_e0.06.fasta
                URL_HASH SHA256=b107238db9e0c0515b33fff570a787a86126789a0341bd2fdb52c6c607772f8d)
declare_datasource (FILE stellar_truth.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/stellar_truth.gff
                URL_HASH SHA256=45be895caedf69070e3433b5b912f7a20e2ac8ffe227e762fb33e5b31d43106a)


declare_datasource (FILE 16bins13window1error.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/16bins13window1error.gff
                URL_HASH SHA256=28dc2cffdd32bb8a7bf2a8826280246103a518468bba32e65ec3c121e00c0fde)
declare_datasource (FILE 16bins13window1error.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/16bins13window1error.gff.out
                URL_HASH SHA256=89e61426004aa15bff39de90b4cd2d7e9080dc19cc3596a797f00d7c8f0c95c0)
declare_datasource (FILE 16bins13window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/16bins13window.ibf
                URL_HASH SHA256=56ba39465e297b128f58544c45fe8fb20c742c505f29ce608b45d33a2960b9a7)
declare_datasource (FILE 16bins15window1error.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/16bins15window1error.gff
                URL_HASH SHA256=28dc2cffdd32bb8a7bf2a8826280246103a518468bba32e65ec3c121e00c0fde)
declare_datasource (FILE 16bins15window1error.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/16bins15window1error.gff.out
                URL_HASH SHA256=66d219613d6a715bbf6cd282868ee31612147287471b7e1820ca77bc370dec9d)
declare_datasource (FILE 16bins15window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/16bins15window.ibf
                URL_HASH SHA256=40237ba1d46b7894eaa7f59c311c9fda74d2d544d5b481581fe03feef78899cd)
declare_datasource (FILE 4bins13window1error.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/4bins13window1error.gff
                URL_HASH SHA256=28dc2cffdd32bb8a7bf2a8826280246103a518468bba32e65ec3c121e00c0fde)
declare_datasource (FILE 4bins13window1error.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/4bins13window1error.gff.out
                URL_HASH SHA256=5d285b543887e94829f15112b8d3c9659d48ff61a74cb216f2fa9f4bb54b4c90)
declare_datasource (FILE 4bins13window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/4bins13window.ibf
                URL_HASH SHA256=cb0a574e08665bd478213d1eed2e2af886e3e0fd8dd2c100b9e457120c458096)
declare_datasource (FILE 4bins15window1error.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/4bins15window1error.gff
                URL_HASH SHA256=28dc2cffdd32bb8a7bf2a8826280246103a518468bba32e65ec3c121e00c0fde)
declare_datasource (FILE 4bins15window1error.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/4bins15window1error.gff.out
                URL_HASH SHA256=5d285b543887e94829f15112b8d3c9659d48ff61a74cb216f2fa9f4bb54b4c90)
declare_datasource (FILE 4bins15window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/4bins15window.ibf
                URL_HASH SHA256=3cffc05e703c029df77d84947293ffabb1993f20ce51446aebf2883e08f58468)
declare_datasource (FILE dummy_reads.fastq
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/dummy_reads.fastq
                URL_HASH SHA256=f1aa9ca0fb0b87393923848f0389cc3fb5cfd4841566afaf72e6c55829b64d73)
declare_datasource (FILE query.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/query.fasta
                URL_HASH SHA256=23ba85ef50015c386b9e23e6f7f63ccc19df89bd9ae09e9a3be4425b7887f106)
declare_datasource (FILE query.fastq
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/query.fastq
                URL_HASH SHA256=cf44a9c49b3c68f43a2800bf791d215704b50d408fc2ddcdd754d976adb69bea)
declare_datasource (FILE query_meta.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/query_meta.txt
                URL_HASH SHA256=1eb7e99026c694bddfdd61125084264d1b2a526a174aae5c8422c418a29ad9f0)
declare_datasource (FILE query_seg_meta.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/query_seg_meta.txt
                URL_HASH SHA256=0a450c09f38f830b7ecf5b460313661cc39e48f9172d48ec1ccc1b68673fb3af)
declare_datasource (FILE ref.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/ref.fasta
                URL_HASH SHA256=30ed460bfe4838a6ce3e97dff22b42c9312b0c801c8d671dbe82f6abca265f4e)
declare_datasource (FILE ref_meta.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/ref_meta.txt
                URL_HASH SHA256=cfaea330c4abde12e75cec5ae8b74ffd985d2b1d4ad1620b72e064f17488e1d5)
declare_datasource (FILE seg_meta150overlap16bins.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/seg_meta150overlap16bins.txt
                URL_HASH SHA256=421c07c3c4c72d79fa4e1a24e03b992d3584a169ad4ed2738e34f8754b10c6e8)
declare_datasource (FILE seg_meta150overlap4bins.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/seg_meta150overlap4bins.txt
                URL_HASH SHA256=651db241a6494e1b130d64cf4f4211a17373ea8c4f60a21b846899c741d87eae)
declare_datasource (FILE stellar.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/stellar.gff
                URL_HASH SHA256=fa2c3f23b4b4b9a2f5bc6144c08bfe53bda1fe1754f2e2edc26315b13228b8ac)
