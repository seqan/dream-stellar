cmake_minimum_required (VERSION 3.16)

include (cmake/app_datasources.cmake)

declare_datasource (FILE database.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/split/database.fasta
                URL_HASH SHA256=7c7a8fcdd52a932cda76219f24024c1624292377103d9fd5a55abd288c6072be)
declare_datasource (FILE single_query.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single_query.fasta
                URL_HASH SHA256=387d0a3f091dd2b89af3498a2c92f4482279a42b718e9408af6307ad6ab0d293)
declare_datasource (FILE single_reference.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single_reference.fasta
                URL_HASH SHA256=53d633474b01a68927d3ab1fd970b200e96403bb1fdcc53feb0367a2093be273)
declare_datasource (FILE various_chromosome_lengths.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/split/various_chromosome_lengths.fasta
                URL_HASH SHA256=7c7a8fcdd52a932cda76219f24024c1624292377103d9fd5a55abd288c6072be)


declare_datasource (FILE 50overlap16bins13window1errors.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/50overlap16bins13window1errors.gff.out
                URL_HASH SHA256=382ad795e3827d69600824d1d3c539e04ac2472dbb43c9fb00934c2beac9ea58)
declare_datasource (FILE 50overlap16bins13window.bin
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/50overlap16bins13window.bin
                URL_HASH SHA256=8cbd9d673c39a729b11758f9db7c1288cefecf76a43b2222fa4b117915905eff)
declare_datasource (FILE 50overlap16bins13window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/50overlap16bins13window.ibf
                URL_HASH SHA256=6d5d63cd4b47d75629da3e87b13c0944739b1d45c8732c335fedb38ca7e1ab50)
declare_datasource (FILE 50overlap16bins15window1errors.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/50overlap16bins15window1errors.gff.out
                URL_HASH SHA256=382ad795e3827d69600824d1d3c539e04ac2472dbb43c9fb00934c2beac9ea58)
declare_datasource (FILE 50overlap16bins15window.bin
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/50overlap16bins15window.bin
                URL_HASH SHA256=8cbd9d673c39a729b11758f9db7c1288cefecf76a43b2222fa4b117915905eff)
declare_datasource (FILE 50overlap16bins15window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/50overlap16bins15window.ibf
                URL_HASH SHA256=e63623884bf43d0d88b353134a8a159d34e4cc36539dd485c876aa7c194f7800)
declare_datasource (FILE 50overlap4bins13window1errors.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/50overlap4bins13window1errors.gff.out
                URL_HASH SHA256=f4d5f38e127cb37deb3a3b9c48f5434f3f0a7b8ae64d0a4d09359a7f8233b828)
declare_datasource (FILE 50overlap4bins13window.bin
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/50overlap4bins13window.bin
                URL_HASH SHA256=39c5ad0fefb8beedb1d3884930f184bb812748e7111b2416a07f22509f5f6d76)
declare_datasource (FILE 50overlap4bins13window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/50overlap4bins13window.ibf
                URL_HASH SHA256=50095ee2e49c760ec949394b42f0c2a62ad3441b6f0019aa045b92673192a0f7)
declare_datasource (FILE 50overlap4bins15window1errors.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/50overlap4bins15window1errors.gff.out
                URL_HASH SHA256=bdf41b5a2c35887c393daae1248f47b0d22b4043423b78b17059fc9840a07c7e)
declare_datasource (FILE 50overlap4bins15window.bin
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/50overlap4bins15window.bin
                URL_HASH SHA256=39c5ad0fefb8beedb1d3884930f184bb812748e7111b2416a07f22509f5f6d76)
declare_datasource (FILE 50overlap4bins15window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/split/single/50overlap4bins15window.ibf
                URL_HASH SHA256=ffc3bd83d5cf1d7fe147495f3d9dfc8ff7a24121a1b11735b3c30362d731c6ff)


declare_datasource (FILE 20overlap16bins.bin
                URL ${CMAKE_SOURCE_DIR}/test/data/split/multi/20overlap16bins.bin
                URL_HASH SHA256=0abef0bccab05dfcfacc2efe7659df5c42c753765b9ad41dbef94a27665bcf7a)
declare_datasource (FILE 20overlap16bins.index
                URL ${CMAKE_SOURCE_DIR}/test/data/split/multi/20overlap16bins.index
                URL_HASH SHA256=42ce82b38c20317a93bbca319ba58dea1f0d42429a70d943b8d399a407140d50)
declare_datasource (FILE 20overlap4bins.bin
                URL ${CMAKE_SOURCE_DIR}/test/data/split/multi/20overlap4bins.bin
                URL_HASH SHA256=59b774833bb43bf07d4a92c0a6bc223f5d64b6de0d271ddc242b99e757ba18a8)
declare_datasource (FILE 20overlap4bins.index
                URL ${CMAKE_SOURCE_DIR}/test/data/split/multi/20overlap4bins.index
                URL_HASH SHA256=0ad6c108fe900a207828bbffb61f2eee69dd46f847f67dd37283e838ee3a23e7)


declare_datasource (FILE write_out_20_16_reference_metadata.bin
                URL ${CMAKE_SOURCE_DIR}/test/data/split/write_out_20_16/reference_metadata.bin
                URL_HASH SHA256=781c0c9d9db6c4c86a1679980e7df8c349ef37a15946f6a29021264f8eccaee5)
declare_datasource (FILE write_out_20_16_reference_metadata.index
                URL ${CMAKE_SOURCE_DIR}/test/data/split/write_out_20_16/reference_metadata.index
                URL_HASH SHA256=6776807dcf57d98daa4f194278b82e4c548a901bc99a6ec4485f970ae1fde61b)
declare_datasource (FILE write_out_20_4_reference_metadata.bin
                URL ${CMAKE_SOURCE_DIR}/test/data/split/write_out_20_4/reference_metadata.bin
                URL_HASH SHA256=1b2c693ad5cc281f4eda14fd74f3eaf9cddcbed57289e8a45f3d10a5251bdb70)
declare_datasource (FILE write_out_20_4_reference_metadata.index
                URL ${CMAKE_SOURCE_DIR}/test/data/split/write_out_20_4/reference_metadata.index
                URL_HASH SHA256=445fcf68f8c165a777eb70b0826c099b32ce28baebf15124496475f09e3ae5a3)
declare_datasource (FILE 8bins19window.bin
                URL ${CMAKE_SOURCE_DIR}/test/data/build/8bins19window.bin
                URL_HASH SHA256=ddaec5fb5fd9785ba733c3eb6ae5727073b3577cf7a9681c7c67c810feace06a)
declare_datasource (FILE 8bins19window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/build/8bins19window.ibf
                URL_HASH SHA256=256286a20cf7d438721deb78f2b1ad0fbb1a453e41ee8e263552ea4682dd6853)
declare_datasource (FILE 8bins23window.bin
                URL ${CMAKE_SOURCE_DIR}/test/data/build/8bins23window.bin
                URL_HASH SHA256=ddaec5fb5fd9785ba733c3eb6ae5727073b3577cf7a9681c7c67c810feace06a)
declare_datasource (FILE 8bins23window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/build/8bins23window.ibf
                URL_HASH SHA256=82cd86856b7aea7e3513f64153c42458f6a9bdd512114b7b0ec50fbf46413e48)
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
declare_datasource (FILE bin_meta.index
                URL ${CMAKE_SOURCE_DIR}/test/data/build/bin_meta.index
                URL_HASH SHA256=7b687e59bf717726dc0a2f0f97dc04cccf478e3266b4411d883359a46cb61f7b)
declare_datasource (FILE bin_paths.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/build/bin_paths.txt
                URL_HASH SHA256=614e23263b689c7b4cc0ae41e99aeb5b43b351f865b4604f892320f2cc4377c7)
declare_datasource (FILE index.bin
                URL ${CMAKE_SOURCE_DIR}/test/data/build/index.bin
                URL_HASH SHA256=f4a3dec17b486d55319a385da189709e6678c1cc03b4224d98dd9cb9c3b247f0)
declare_datasource (FILE index_copy_without_meta.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/build/index_copy_without_meta.ibf
                URL_HASH SHA256=256286a20cf7d438721deb78f2b1ad0fbb1a453e41ee8e263552ea4682dd6853)
declare_datasource (FILE index.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/build/index.ibf
                URL_HASH SHA256=cea3e922e2401224f9873bdea6eba2490e04d992b7a54062fdd138d250861293)


declare_datasource (FILE 8bins19window0error100pattern1query_every.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error100pattern1query_every.gff.out
                URL_HASH SHA256=86cb78ed0ee5cef739eb9820436385979fbf0dd5d47b5a0b76d0828ece1c9731)
declare_datasource (FILE 8bins19window0error100pattern50query_every.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error100pattern50query_every.gff.out
                URL_HASH SHA256=86cb78ed0ee5cef739eb9820436385979fbf0dd5d47b5a0b76d0828ece1c9731)
declare_datasource (FILE 8bins19window0error50pattern1query_every.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error50pattern1query_every.gff.out
                URL_HASH SHA256=605edcd589d72b1b4c188320ed8c82b3ffed829b81a4de6d60d1faaa397bebe7)
declare_datasource (FILE 8bins19window0error50pattern50query_every.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window0error50pattern50query_every.gff.out
                URL_HASH SHA256=605edcd589d72b1b4c188320ed8c82b3ffed829b81a4de6d60d1faaa397bebe7)
declare_datasource (FILE 8bins19window1error100pattern1query_every.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error100pattern1query_every.gff.out
                URL_HASH SHA256=5e012ca72c80eb21d105a4c5b61535c18170ef2419416b44e099dea0be49c5c7)
declare_datasource (FILE 8bins19window1error100pattern50query_every.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error100pattern50query_every.gff.out
                URL_HASH SHA256=5e012ca72c80eb21d105a4c5b61535c18170ef2419416b44e099dea0be49c5c7)
declare_datasource (FILE 8bins19window1error50pattern1query_every.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error50pattern1query_every.gff.out
                URL_HASH SHA256=055546311f2fb528a019d0e0b35b321bbaa13cda4caabaa0b236a83c3b293c99)
declare_datasource (FILE 8bins19window1error50pattern50query_every.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins19window1error50pattern50query_every.gff.out
                URL_HASH SHA256=f12f6de0547895b1920e08575db159ddc3d93cfec038dc81df779d963799583e)
declare_datasource (FILE 8bins23window0error100pattern1query_every.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error100pattern1query_every.gff.out
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE 8bins23window0error100pattern50query_every.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error100pattern50query_every.gff.out
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE 8bins23window0error50pattern1query_every.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error50pattern1query_every.gff.out
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE 8bins23window0error50pattern50query_every.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error50pattern50query_every.gff.out
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE 8bins23window1error100pattern1query_every.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error100pattern1query_every.gff.out
                URL_HASH SHA256=d232f402bced51cd8e07175058adbcabe6e99eb5187f66445abc0b687ec5a2be)
declare_datasource (FILE 8bins23window1error100pattern50query_every.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error100pattern50query_every.gff.out
                URL_HASH SHA256=d232f402bced51cd8e07175058adbcabe6e99eb5187f66445abc0b687ec5a2be)
declare_datasource (FILE 8bins23window1error50pattern1query_every.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error50pattern1query_every.gff.out
                URL_HASH SHA256=c58b9bf7f3188dd6ba58566bbfdaf5a4038c2af5e38ec49649f4ce614fb114d8)
declare_datasource (FILE 8bins23window1error50pattern50query_every.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error50pattern50query_every.gff.out
                URL_HASH SHA256=41d4bc1740f09e9425b98e5bde7b781229d95685f189008f6c922049251a82e0)
declare_datasource (FILE query.fq
                URL ${CMAKE_SOURCE_DIR}/test/data/search/query.fq
                URL_HASH SHA256=65fbd58c14ca2b4c2274f44fff14dbfce54dc04a89cf6759e1a69cecba933130)


declare_datasource (FILE 16bins50overlap_dream_all.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/16bins50overlap_dream_all.gff
                URL_HASH SHA256=3ecd0e55e704cfd71442bd16805fe587de720e646cbe2d13675ed6249b30045f)
declare_datasource (FILE 16bins50overlap_reference_metadata.arg
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/16bins50overlap_reference_metadata.arg
                URL_HASH SHA256=b2be63df8dd27c404df39d757f99e07b5b39233950719ad70936f491dcb90baf)
declare_datasource (FILE 16bins50overlap_reference_metadata.bin
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/16bins50overlap_reference_metadata.bin
                URL_HASH SHA256=5a8a881c55ff6b4339a1b4eadb2102af2f64202047b503ee8186604e91d14554)
declare_datasource (FILE 16bins50overlap_reference_metadata.index
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/16bins50overlap_reference_metadata.index
                URL_HASH SHA256=6b5436b52b4c2fa2d2a045700ca00f42a680e421768b13a3e7f21da6c30c66eb)
declare_datasource (FILE 8bins50overlap_dream_all.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/8bins50overlap_dream_all.gff
                URL_HASH SHA256=f03c93ddb758a7e9ef89e3243dca9fb49b97a1ba3239408ffc30f8ff486982c8)
declare_datasource (FILE 8bins50overlap_reference_metadata.arg
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/8bins50overlap_reference_metadata.arg
                URL_HASH SHA256=5851936bbbea6fc78fd879f60dc00796c0860c2700161d4d6f0e7d6991acad95)
declare_datasource (FILE 8bins50overlap_reference_metadata.bin
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/8bins50overlap_reference_metadata.bin
                URL_HASH SHA256=5dab94fb005266b11e649725f98090147670aee5679346dcb8a93163dc98c6f6)
declare_datasource (FILE 8bins50overlap_reference_metadata.index
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/8bins50overlap_reference_metadata.index
                URL_HASH SHA256=231e0d7db9391c82a7ddc2f1da1fe8b6a7ac6f9f62dcc5a0f375f2e6992686b5)
declare_datasource (FILE multi_seq_query.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/multi_seq_query.fasta
                URL_HASH SHA256=6d1260dc701802924487453c19715044cbeaa0f42021be8f2996bbaac1f24c58)
declare_datasource (FILE multi_seq_ref.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/multi_seq_ref.fasta
                URL_HASH SHA256=a37f4be29ec99b66efb6ac235224b3145aadf8d5d6ff2c5c2f5324890170ce92)
declare_datasource (FILE stellar_truth.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/stellar_truth.gff
                URL_HASH SHA256=95bf8d1fcbcfde4dfea3cd2055bcf35be161e6b21519e2c936b3595ef37c017b)
declare_datasource (FILE stellar_truth_num12_dis13.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/stellar_truth_num12_dis13.gff
                URL_HASH SHA256=95bf8d1fcbcfde4dfea3cd2055bcf35be161e6b21519e2c936b3595ef37c017b)
declare_datasource (FILE stellar_truth_num12_dis3.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/stellar_truth_num12_dis3.gff
                URL_HASH SHA256=3ba650aa865f8190f21704275c9006e31a75c23b8adc27b1572d0f8a370285e6)
declare_datasource (FILE stellar_truth_num12_dis8.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/stellar_truth_num12_dis8.gff
                URL_HASH SHA256=18203e3ca735c4416fcc2444013640f13326babff0eea4456de604f0e1882e3e)
declare_datasource (FILE stellar_truth_num3_dis13.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/stellar_truth_num3_dis13.gff
                URL_HASH SHA256=315f57cedc484dcf074c4d8f0c199d73480fe0d9d5a58e5072df28c8e7d1694f)
declare_datasource (FILE stellar_truth_num3_dis3.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/stellar_truth_num3_dis3.gff
                URL_HASH SHA256=3ba650aa865f8190f21704275c9006e31a75c23b8adc27b1572d0f8a370285e6)
declare_datasource (FILE stellar_truth_num3_dis8.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/stellar_truth_num3_dis8.gff
                URL_HASH SHA256=f11cb143f32804c9fb51ee5c865fcb08fa1862b2fb67557ba95d17b38a4fb0e5)
declare_datasource (FILE stellar_truth_num9_dis13.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/stellar_truth_num9_dis13.gff
                URL_HASH SHA256=95bf8d1fcbcfde4dfea3cd2055bcf35be161e6b21519e2c936b3595ef37c017b)
declare_datasource (FILE stellar_truth_num9_dis3.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/stellar_truth_num9_dis3.gff
                URL_HASH SHA256=3ba650aa865f8190f21704275c9006e31a75c23b8adc27b1572d0f8a370285e6)
declare_datasource (FILE stellar_truth_num9_dis8.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/consolidate/stellar_truth_num9_dis8.gff
                URL_HASH SHA256=18203e3ca735c4416fcc2444013640f13326babff0eea4456de604f0e1882e3e)


declare_datasource (FILE 1error.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/1error.gff
                URL_HASH SHA256=320bd247df63f0af37b069914a690e168460666f0c1b6040d3138bf387e2cd4a)
declare_datasource (FILE 1error.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/1error.gff.out
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE 1error_stellar.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/1error_stellar.gff
                URL_HASH SHA256=01993f28b0973e612a7cc3e84abdbe551c9b47a6cc7507106ff4b48071c21613)
declare_datasource (FILE 2error_50pattern_index.arg
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/2error_50pattern_index.arg
                URL_HASH SHA256=0953aff9a979cd52891a2371af99cd8560c12749c2a2e6f4df91ee6dc6402fc4)
declare_datasource (FILE 2error_50pattern_index.bin
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/2error_50pattern_index.bin
                URL_HASH SHA256=dd3f0b77ca46a3792c024d2ceb3036fb46e9c4698e3dd7accc52e5bdd9e4b6cf)
declare_datasource (FILE 2error.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/2error.gff
                URL_HASH SHA256=1e00e21cf8301a5d14dfdc60e422fb4f6234289dcd4cefb7a89cf2e76489c8ff)
declare_datasource (FILE 2error.gff.out
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/2error.gff.out
                URL_HASH SHA256=e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855)
declare_datasource (FILE 2error_stellar.gff
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/2error_stellar.gff
                URL_HASH SHA256=85cef348cd514cd12c442c71c7b44a6e44da4d3ea99e56752b3cc88d6f8d5b3f)
declare_datasource (FILE dummy_reads.fastq
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/dummy_reads.fastq
                URL_HASH SHA256=bf046a665167d983c19cf49c0366e09b0773860a679db97ed2a6a6e6a19e4cd9)
declare_datasource (FILE meta_param_deduction.arg
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/meta_param_deduction.arg
                URL_HASH SHA256=80fb0184ba1af94a20e263c8f20e0cf96358c2afc5c38f758a495cf505634440)
declare_datasource (FILE meta_param_deduction.bin
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/meta_param_deduction.bin
                URL_HASH SHA256=19d9f4fd273cf03754e3f2dda4b3e767d6c96f8a227f5a5c5231262b18296f13)
declare_datasource (FILE query.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/query.fasta
                URL_HASH SHA256=40246c2de99c2d41508f3eec7fbfb1006001e6132c4b2fbdbe9ba500ce8be887)
declare_datasource (FILE reference_metadata.arg
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/reference_metadata.arg
                URL_HASH SHA256=a8541581af7ce61c953d43f5016bf27a35fd591be0c9e3f8a8f64917e3c1218f)
declare_datasource (FILE ref.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/ref.fasta
                URL_HASH SHA256=47f808d207c4c90afebbe1c8ab28990ec0e3e777c75ec787099279005428f3da)
declare_datasource (FILE seg_files.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/dream/seg_files.txt
                URL_HASH SHA256=11bfde0a47b2f2f21e69e5ad5375ab3994d0475c4bda90cebdec5e87e95beed9)
declare_datasource (FILE s11111111.bin
                URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s11111111.bin
                URL_HASH SHA256=620a661ed672d9098048024347057c8f29c3ba595b43fbeccbdf6a1242642660)
declare_datasource (FILE s111110011111.bin
                URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s111110011111.bin
                URL_HASH SHA256=620a661ed672d9098048024347057c8f29c3ba595b43fbeccbdf6a1242642660)
declare_datasource (FILE ref_bin_0.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/prepare/bins/ref_0.fasta
                URL_HASH SHA256=d27be5c9702697cf6e3573f469666f137a2c95b3c354deaab5151102a507a2fb)
declare_datasource (FILE s11111111_ref.0.header
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s11111111/ref.0.header
                    URL_HASH SHA256=2bd3aa799c1689f366f58e468dc2b73537463e2244e00ef3eac1b055bef130c8)
declare_datasource (FILE s11111111_ref.0.minimiser
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s11111111/ref.0.minimiser
                    URL_HASH SHA256=b92f326fd1bc48b0858f65a043e48ee8cff275d1b605cc11f83951a9bbcf0d4f)
declare_datasource (FILE s111110011111_ref.0.header
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s111110011111/ref.0.header
                    URL_HASH SHA256=43edfccb7524b9334149e1bd965818507c76adef11ed2531cf1f7f0f7cd432a3)
declare_datasource (FILE s111110011111_ref.0.minimiser
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s111110011111/ref.0.minimiser
                    URL_HASH SHA256=7c9611e021878c99eb3a87fceec027988f713234dda15b6048d030b655615c50)
declare_datasource (FILE ref_bin_1.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/prepare/bins/ref_1.fasta
                URL_HASH SHA256=486d3e529acdd263896123389ece34774ed4448df33b5e6ae1ced672526a2efe)
declare_datasource (FILE s11111111_ref.1.header
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s11111111/ref.1.header
                    URL_HASH SHA256=a04fafe6af22a41ad26eaaa43434df0fbdd975c67645d84a35de736186b5a680)
declare_datasource (FILE s11111111_ref.1.minimiser
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s11111111/ref.1.minimiser
                    URL_HASH SHA256=5abf0ea1fdd97d5bd0ac21445902f91d69e5652f5bf39cac9eb374fc5b54f483)
declare_datasource (FILE s111110011111_ref.1.header
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s111110011111/ref.1.header
                    URL_HASH SHA256=f7d61c0d8039c2441f43293ff490d1be3a1023e2467ca7309a06efaf6ebfa542)
declare_datasource (FILE s111110011111_ref.1.minimiser
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s111110011111/ref.1.minimiser
                    URL_HASH SHA256=e67e20c44fa01bf49923379fda6346afc94ba0fabb1090a05fb1d6033e2ca07a)
declare_datasource (FILE ref_bin_2.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/prepare/bins/ref_2.fasta
                URL_HASH SHA256=76202a44ea78ea01420192e1266c5618b5e8131e65dee9c129c726240a687063)
declare_datasource (FILE s11111111_ref.2.header
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s11111111/ref.2.header
                    URL_HASH SHA256=efacd3cfeaec4c6e17d2e54e846ca24d7db6e65b2709980a47616a60c89a5d90)
declare_datasource (FILE s11111111_ref.2.minimiser
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s11111111/ref.2.minimiser
                    URL_HASH SHA256=4cf2c1243a0a9b41818bea7d65873764063aeeed2c7428ea78a3ba8a345682fb)
declare_datasource (FILE s111110011111_ref.2.header
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s111110011111/ref.2.header
                    URL_HASH SHA256=28b1555f94ffb8e7fc62857df31ca0577419b23e7b3c80fc25c5e8cc449e55cc)
declare_datasource (FILE s111110011111_ref.2.minimiser
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s111110011111/ref.2.minimiser
                    URL_HASH SHA256=552735a13f3522a4fcb802fe7220e67f1b3e02023709c4ac7834dbd83bdbe3b0)
declare_datasource (FILE ref_bin_3.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/prepare/bins/ref_3.fasta
                URL_HASH SHA256=da5f19c86476464aeaa483baf47b387a30e4d35bffd0e4d5c8cc30b86171458b)
declare_datasource (FILE s11111111_ref.3.header
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s11111111/ref.3.header
                    URL_HASH SHA256=b68d2e2d414ad85b241a95cc8a7803e7287ad91b141e21b6dea3d0c52e4383b5)
declare_datasource (FILE s11111111_ref.3.minimiser
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s11111111/ref.3.minimiser
                    URL_HASH SHA256=e2dae13eb7002cb5ce0bc1e26e76608a9b171649137ae85eaa8367fadef7ecf7)
declare_datasource (FILE s111110011111_ref.3.header
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s111110011111/ref.3.header
                    URL_HASH SHA256=45f6c80ca1fa9e67a19bcaf0dc94241bdbb69bfce064259190726c77d94f72a4)
declare_datasource (FILE s111110011111_ref.3.minimiser
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s111110011111/ref.3.minimiser
                    URL_HASH SHA256=e1f96c8ec63d417c824dc052a55ac7093dfe79e09db331d7a973f52572b94dd4)
declare_datasource (FILE ref_bin_4.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/prepare/bins/ref_4.fasta
                URL_HASH SHA256=eaf85f135a9197732e6171b6652493f897e225b9970befea7945ff01e879688b)
declare_datasource (FILE s11111111_ref.4.header
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s11111111/ref.4.header
                    URL_HASH SHA256=02ed6fd31d1adb0fe55d58f2f22facb9be51193cab24e634a9380400b7f04ebd)
declare_datasource (FILE s11111111_ref.4.minimiser
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s11111111/ref.4.minimiser
                    URL_HASH SHA256=644c16cfdd9647aecf657609de328d9dcb8b275d0de082f3acf06572ae92c8f6)
declare_datasource (FILE s111110011111_ref.4.header
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s111110011111/ref.4.header
                    URL_HASH SHA256=e89651b786973c8d0f118e223f26843af3a01b8df55c7cb712c03e993578276a)
declare_datasource (FILE s111110011111_ref.4.minimiser
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s111110011111/ref.4.minimiser
                    URL_HASH SHA256=e23940349524eccba29579729b308c980ec3876b34a9a69c465227efcc920524)
declare_datasource (FILE ref_bin_5.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/prepare/bins/ref_5.fasta
                URL_HASH SHA256=0084dceed91ba50fd25675a82b92c51784284ebf84d4904f1eaa825c8e8add49)
declare_datasource (FILE s11111111_ref.5.header
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s11111111/ref.5.header
                    URL_HASH SHA256=b12fb8c4ff2e6ec4deddf5883e7f89a3be27ef386e5b0d242f5522ce93d45c70)
declare_datasource (FILE s11111111_ref.5.minimiser
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s11111111/ref.5.minimiser
                    URL_HASH SHA256=e35c85d430b4e2f58e72888f0f427abd93b9504415a564a274095b69969f60f8)
declare_datasource (FILE s111110011111_ref.5.header
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s111110011111/ref.5.header
                    URL_HASH SHA256=c3d648cc5aad702a5648b0b3c9135fd95d92c5d40d68f0c1433059d8ff1e373f)
declare_datasource (FILE s111110011111_ref.5.minimiser
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s111110011111/ref.5.minimiser
                    URL_HASH SHA256=ac2ebb0d0c64e5b9951c5240a00b84641a72b960d8e1f4bc2e34a2f9bd12e842)
declare_datasource (FILE ref_bin_6.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/prepare/bins/ref_6.fasta
                URL_HASH SHA256=0ab92343a1bd9610601183362f8719c397265a42cf47b7b8719bf8b66c1636e5)
declare_datasource (FILE s11111111_ref.6.header
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s11111111/ref.6.header
                    URL_HASH SHA256=167b50db02aa4c53ed11c0505340ad09b83c7f9088dba990a23273643a2f483b)
declare_datasource (FILE s11111111_ref.6.minimiser
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s11111111/ref.6.minimiser
                    URL_HASH SHA256=f593ca9e1672ecc9d5b4fa9a9d9cc4f1c721f7dd9fa52ac82ba4288a24321473)
declare_datasource (FILE s111110011111_ref.6.header
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s111110011111/ref.6.header
                    URL_HASH SHA256=1c42baa7f4a1ebc2d0aa9746634e6f775232c4fb7514df8ddd61429f5289415c)
declare_datasource (FILE s111110011111_ref.6.minimiser
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s111110011111/ref.6.minimiser
                    URL_HASH SHA256=338cc8901100b55c406ade8a6a7802db7339f72e9df55f5f876d0042f838a5d0)
declare_datasource (FILE ref_bin_7.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/prepare/bins/ref_7.fasta
                URL_HASH SHA256=7a94f3b63c2cdc1c4d2d58e51345a5447aa640c640b8bc44a501ec5c84c255e6)
declare_datasource (FILE s11111111_ref.7.header
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s11111111/ref.7.header
                    URL_HASH SHA256=167b50db02aa4c53ed11c0505340ad09b83c7f9088dba990a23273643a2f483b)
declare_datasource (FILE s11111111_ref.7.minimiser
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s11111111/ref.7.minimiser
                    URL_HASH SHA256=f593ca9e1672ecc9d5b4fa9a9d9cc4f1c721f7dd9fa52ac82ba4288a24321473)
declare_datasource (FILE s111110011111_ref.7.header
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s111110011111/ref.7.header
                    URL_HASH SHA256=1c42baa7f4a1ebc2d0aa9746634e6f775232c4fb7514df8ddd61429f5289415c)
declare_datasource (FILE s111110011111_ref.7.minimiser
                    URL ${CMAKE_SOURCE_DIR}/test/data/prepare/s111110011111/ref.7.minimiser
                    URL_HASH SHA256=338cc8901100b55c406ade8a6a7802db7339f72e9df55f5f876d0042f838a5d0)
