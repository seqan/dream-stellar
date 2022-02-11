# valik [![build status][1]][2] [![codecov][3]][4]
<!--
    Above uses reference-style links with numbers.
    See also https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet#links.

    For example, `[![build status][1]][2]` evaluates to the following:
        `[link_text][2]`
        `[2]` is a reference to a link, i.e. `[link_text](https://...)`

        `[link_text]` = `[![build status][1]]`
        `[1]` is once again a reference to a link - this time an image, i.e. `[![build status](https://...)]
        `![build status]` is the text that should be displayed if the linked resource (`[1]`) is not available

    `[![build status][1]][2]` hence means:
    Show the picture linked under `[1]`. In case it cannot be displayed, show the text "build status" instead.
    The picture, or alternative text, should link to `[2]`.
-->

<!--
    This is the CI badge image:
        `https://img.shields.io/github/workflow/status/` - we do not use GitHub's badges as they are not customisable.
        `/seqan/app-template/` - owner/repository
        `CI%20on%20Linux` - name of the workflow as encoded URL (e.g., whitespace = %20)
        `master` - branch to show
        `?style=flat&logo=github` - use a GitHub-style badge
        `&label=App-Template%20CI` - text on the badge
        `"Open GitHub actions page"` - this text will be shown on hover
-->
[1]: https://img.shields.io/github/workflow/status/eaasna/valik/CI%20on%20Linux/master?style=flat&logo=github&label=valik%20CI "Open GitHub actions page"
<!--
    This is the CI badge link:
        `https://github.com/seqan/app-template/actions` - actions page of owner(seqan)/repository(app-template)
        `?query=branch%3Amaster` - only show actions that ran on the mater branch
-->
[2]: https://github.com/eaasna/valik/actions?query=branch%3Amaster
<!--
    This is the Codecov badge image:
        Codecov offers badges: https://app.codecov.io/gh/seqan/app-template/settings/badge
        While being logged in into Codecov, navigate to Settings->Badge and copy the markdown badge.
        Copy the image part of the markdown badge here.
    `"Open Codecov page"` - this text will be shown on hover
-->
[3]: https://codecov.io/gh/eaasna/valik/branch/master/graph/badge.svg?token=ZKGJTQ55MF
<!--
    This is the Codecov badge link:
        Codecov offers badges: https://app.codecov.io/gh/seqan/app-template/settings/badge
        While being logged in into Codecov, navigate to Settings->Badge and copy the markdown badge.
        Copy the URL part of the markdown badge here.
-->
[4]: https://codecov.io/gh/eaasna/valik

## Quick run
`valik split example_data/64/bins/bin_00.fasta --overlap 150 --bins 64`

`valik build bin_paths.txt --threads 8 --output index.out --size 80m`

`valik search --index index.out --query example_data/64/reads/all.fastq --pattern 50 --output matches.out --overlap 10`

### Distributed local search
The valik application employs an IBF based prefilter (Estonian: _valik_) for searching approximate local matches in a nucleotide sequence database. The IBF is created from the (w,k)-minimiser content of the reference database. The filter excludes parts of the reference database for each query read. Only reference sequences where an approximate local match for the query sequence was found are retained.
A local match is defined as:
* length >= `pattern`
* errors <= `errors`

where `pattern` is the pattern size and `errors` the allowed number of errors. Each read is divided into multiple possibly overlapping pattern. The (w, k)-minimiser content of each window is then queried in the IBF.

## Download and Installation

<details><summary>Prerequisites (click to expand)</summary>

* CMake >= 3.8
* GCC 9, 10 or 11 (most recent minor version)
* git

Refer to the [Seqan3 Setup Tutorial](https://docs.seqan.de/seqan/3-master-user/setup.html) for more in depth information.
</details>

<details><summary>Download current master branch (click to expand)</summary>

```bash
git clone --recurse-submodules https://github.com/eaasna/valik
```

</details>

<details><summary>Building (click to expand)</summary>

```bash
cd valik
mkdir -p build
cd build
cmake ..
make
```

The binary can be found in `bin`.

You may want to add the executable to your PATH:
```
export PATH=$(pwd)/bin:$PATH
valik --version
```

</details>

## Example Metagenomic Data and Usage
A toy data set can be found [here](https://ftp.imp.fu-berlin.de/pub/seiler/raptor/).

```bash
wget https://ftp.imp.fu-berlin.de/pub/seiler/raptor/example_data.tar.gz
tar xfz example_data.tar.gz
```

After extraction, the `example_data` will look like:

```console
$ tree -L 2 example_data
example_data
├── 1024
│   ├── bins
│   └── reads
└── 64
    ├── bins
    └── reads
```

The `bins` folder contains a FASTA file for each bin and the `reads` directory contains a FASTQ file for each bin
containing reads from the respective bin (with 2 errors).
Additionally, `mini.fastq` (5 reads of all bins), `all.fastq` (concatenation of all FASTQ files) and `all10.fastq`
(`all.fastq` repeated 10 times) are provided in the `reads` folder.

In the following, we will use the `64` data set.
To build an index over all bins, we first prepare a file that contains one file path per line
(a line corresponds to a bin) and use this file as input:
```
seq -f "example_data/64/bins/bin_%02g.fasta" 0 1 63 > bin_paths.txt
valik build bin_paths.txt --threads 8 --output index.out --size 80m
```

You may be prompted to enable or disable automatic update notifications. For questions, please consult
[the SeqAn documentation](https://github.com/seqan/seqan3/wiki/Update-Notifications).

Afterwards, we can search for all reads from bin 1:

```
valik search --index index.out --query example_data/64/reads/mini.fastq --errors 2 --pattern 50 --output matches.out --overlap 10
```

Each line of the output consists of the read ID (in the toy example these are numbers) and the corresponding bins in
which they were found:
```text
0       0,
1       0,
2       0,
3       0,
4       0,
16384   1,
...
1015812 62,
1032192 63,
1032193 63,
1032194 63,
1032195 63,
1032196 63,
```

For a list of options, see the help pages:
```console
valik --help
valik split --help
valik build --help
valik search --help
```

## Authorship and Copyright
The valik application is based on Raptor. Raptor is being developed by [Enrico Seiler](mailto:enrico.seiler@fu-berlin.de), but also incorporates much work from
other members of [SeqAn](https://www.seqan.de).

### Citation
In your academic works (also comparisons and pipelines) please cite:
  * Seiler, E. et al. (2020). Raptor: A fast and space-efficient pre-filter for querying very large collections of nucleotide sequences. bioRxiv 2020.10.08.330985. doi: https://doi.org/10.1101/2020.10.08.330985

### Supplementary
The subdirectory `util` contains applications and scripts related to the paper.

### License
Raptor is open source software. However, certain conditions apply when you (re-)distribute and/or modify Raptor, please see the [license](https://github.com/seqan/raptor/blob/master/LICENSE.md).
