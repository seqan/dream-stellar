cmake_minimum_required (VERSION 3.8)

include (cmake/app_datasources.cmake)

declare_datasource (FILE 0overlap16bins.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/0overlap16bins.txt
                URL_HASH SHA256=39b3c960ce05e23d3208ab766388819a1e82b8036ae303e0eae37b425f66ef36)
declare_datasource (FILE 0overlap4bins.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/0overlap4bins.txt
                URL_HASH SHA256=88ee7061dc9dd86e7bd4cd8e37424bd73c3a74a7574d0b93d5519580d7cf1470)
declare_datasource (FILE 20overlap16bins.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/20overlap16bins.txt
                URL_HASH SHA256=b4d1c624381a18f120ecda7c4b7330fe34051503119ddefd8e08732fc20dca9f)
declare_datasource (FILE 20overlap4bins.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/20overlap4bins.txt
                URL_HASH SHA256=88ee7061dc9dd86e7bd4cd8e37424bd73c3a74a7574d0b93d5519580d7cf1470)
declare_datasource (FILE chromosome_metadata.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/split/chromosome_metadata.txt
                URL_HASH SHA256=435e36bbdb0d481070aca7a86d3b264359bc0c5029fbdaa48f17b9e0f8ad306b)
declare_datasource (FILE various_chromosome_lengths.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/split/various_chromosome_lengths.fasta
                URL_HASH SHA256=7c7a8fcdd52a932cda76219f24024c1624292377103d9fd5a55abd288c6072be)


declare_datasource (FILE 8bins20window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/build/8bins20window.ibf
                URL_HASH SHA256=1f31b26aadffca282ea18c268fda4b0f4b7620ed9d7aad0e601fcb8836885a39)
declare_datasource (FILE 8bins23window.ibf
                URL ${CMAKE_SOURCE_DIR}/test/data/build/8bins23window.ibf
                URL_HASH SHA256=db60ff29d96b1233736ab804dcc3d3c2a39c587d639ffee13a90aeb62229ed47)
declare_datasource (FILE bin_0.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/build/bin_0.fasta
                URL_HASH SHA256=db34f95329d7dce3e91866709e06a63324c56d7bf8ba623e88429c884f6ea66f)
declare_datasource (FILE bin_1.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/build/bin_1.fasta
                URL_HASH SHA256=10558b31484d0bc95b4fcc826a5cb297e87d897fb46a521ef8f3bbe6455ed89a)
declare_datasource (FILE bin_2.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/build/bin_2.fasta
                URL_HASH SHA256=18eaae83692eb400aa9f6361370239781126b72f12ffa9b43e7b044093951ff6)
declare_datasource (FILE bin_3.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/build/bin_3.fasta
                URL_HASH SHA256=16af87a9032d17544bcacb154ea28b056ec0f2901f70b9e35067f73f3599ecce)
declare_datasource (FILE bin_4.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/build/bin_4.fasta
                URL_HASH SHA256=5ecd0f6508f7b73757abf33c1b0cc6469c0c47332c28d9fff6e20a4240e2ebd2)
declare_datasource (FILE bin_5.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/build/bin_5.fasta
                URL_HASH SHA256=0a649c9bc290de79457b8822688279b65a5a640d205e06ca0af68d81b1c9b81a)
declare_datasource (FILE bin_6.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/build/bin_6.fasta
                URL_HASH SHA256=fbb6d63cf12c0d594ee8acb19d42a46908ff016e311ff87c99136fc7e526b7a0)
declare_datasource (FILE bin_7.fasta
                URL ${CMAKE_SOURCE_DIR}/test/data/build/bin_7.fasta
                URL_HASH SHA256=9c5518c05dd367fbf0a10bf07842ebdd91e0736cbbe1e6d358b0e2bae8e8e48e)
declare_datasource (FILE bin_paths.txt
                URL ${CMAKE_SOURCE_DIR}/test/data/build/bin_paths.txt
                URL_HASH SHA256=614e23263b689c7b4cc0ae41e99aeb5b43b351f865b4604f892320f2cc4377c7)


declare_datasource (FILE 8bins20window0error100pattern1overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins20window0error100pattern1overlap.out
                URL_HASH SHA256=f8cea81a9d1a22b6ebca2a5b2708edb04295dd29fcaa0daf8c7005b55ed474dc)
declare_datasource (FILE 8bins20window0error100pattern40overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins20window0error100pattern40overlap.out
                URL_HASH SHA256=99c978af1caabee56b5a0ab0724aa3b9289ef2d7aa5cde3c6e81991ca69ce5ec)
declare_datasource (FILE 8bins20window0error50pattern1overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins20window0error50pattern1overlap.out
                URL_HASH SHA256=89762f4105f0c66711c2f82a0dd5722cea64a9320c41b59397d476fc83fce3f9)
declare_datasource (FILE 8bins20window0error50pattern40overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins20window0error50pattern40overlap.out
                URL_HASH SHA256=89762f4105f0c66711c2f82a0dd5722cea64a9320c41b59397d476fc83fce3f9)
declare_datasource (FILE 8bins20window1error100pattern1overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins20window1error100pattern1overlap.out
                URL_HASH SHA256=e1d6bc382c78ab4642a26ee56ca0bcb89cf7c57cf5a3e45d5a0cca824d995c7a)
declare_datasource (FILE 8bins20window1error100pattern40overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins20window1error100pattern40overlap.out
                URL_HASH SHA256=a3e397d1590f51846c3e23a2f19f251861b2f85d8dd7aa341a1a64c71caaa108)
declare_datasource (FILE 8bins20window1error50pattern1overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins20window1error50pattern1overlap.out
                URL_HASH SHA256=9d0911adc114b800f49d659fba711782691f4057eacb58a4fc5578e4e3e92f2f)
declare_datasource (FILE 8bins20window1error50pattern40overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins20window1error50pattern40overlap.out
                URL_HASH SHA256=9d0911adc114b800f49d659fba711782691f4057eacb58a4fc5578e4e3e92f2f)
declare_datasource (FILE 8bins23window0error100pattern1overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error100pattern1overlap.out
                URL_HASH SHA256=7ebd8b8ab2c2d6e216ef436b8874a2ed1a386e8f7f564e8772416386170c6409)
declare_datasource (FILE 8bins23window0error100pattern40overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error100pattern40overlap.out
                URL_HASH SHA256=7ebd8b8ab2c2d6e216ef436b8874a2ed1a386e8f7f564e8772416386170c6409)
declare_datasource (FILE 8bins23window0error50pattern1overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error50pattern1overlap.out
                URL_HASH SHA256=7ebd8b8ab2c2d6e216ef436b8874a2ed1a386e8f7f564e8772416386170c6409)
declare_datasource (FILE 8bins23window0error50pattern40overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window0error50pattern40overlap.out
                URL_HASH SHA256=7ebd8b8ab2c2d6e216ef436b8874a2ed1a386e8f7f564e8772416386170c6409)
declare_datasource (FILE 8bins23window1error100pattern1overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error100pattern1overlap.out
                URL_HASH SHA256=89762f4105f0c66711c2f82a0dd5722cea64a9320c41b59397d476fc83fce3f9)
declare_datasource (FILE 8bins23window1error100pattern40overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error100pattern40overlap.out
                URL_HASH SHA256=89762f4105f0c66711c2f82a0dd5722cea64a9320c41b59397d476fc83fce3f9)
declare_datasource (FILE 8bins23window1error50pattern1overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error50pattern1overlap.out
                URL_HASH SHA256=9d0911adc114b800f49d659fba711782691f4057eacb58a4fc5578e4e3e92f2f)
declare_datasource (FILE 8bins23window1error50pattern40overlap.out
                URL ${CMAKE_SOURCE_DIR}/test/data/search/8bins23window1error50pattern40overlap.out
                URL_HASH SHA256=9d0911adc114b800f49d659fba711782691f4057eacb58a4fc5578e4e3e92f2f)
declare_datasource (FILE query.fq
                URL ${CMAKE_SOURCE_DIR}/test/data/search/query.fq
                URL_HASH SHA256=80eed9cdecda0061076b067d09368adce074c14f71f17f07eccd92578236c3fe)
