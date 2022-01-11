# Raptor [![build status][1]][2] [![codecov][3]][4]
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
[1]: https://img.shields.io/github/workflow/status/eaasna/sliding-window/CI%20on%20Linux/master?style=flat&logo=github&label=Sliging%20Window%20CI "Open GitHub actions page"
<!--
    This is the CI badge link:
        `https://github.com/seqan/app-template/actions` - actions page of owner(seqan)/repository(app-template)
        `?query=branch%3Amaster` - only show actions that ran on the mater branch
-->
[2]: https://github.com/eaasna/sliding-window/actions?query=branch%3Amaster
<!--
    This is the Codecov badge image:
        Codecov offers badges: https://app.codecov.io/gh/seqan/app-template/settings/badge
        While being logged in into Codecov, navigate to Settings->Badge and copy the markdown badge.
        Copy the image part of the markdown badge here.
    `"Open Codecov page"` - this text will be shown on hover
-->
[3]: https://codecov.io/gh/eaasna/sliding-window/branch/master/graph/badge.svg?token=ZKGJTQ55MF "Open Codecov page"
<!--
    This is the Codecov badge link:
        Codecov offers badges: https://app.codecov.io/gh/seqan/app-template/settings/badge
        While being logged in into Codecov, navigate to Settings->Badge and copy the markdown badge.
        Copy the URL part of the markdown badge here.
-->
[4]: https://codecov.io/gh/eaasna/sliding-window

### A fast and space-efficient pre-filter for querying very large collections of nucleotide sequences

## Download and Installation
There may be performance benefits when compiling from source, especially when using `-march=native` as compiler directive.

### Install with bioconda (Linux)
[![install with bioconda](https://img.shields.io/badge/install%20with-bioconda-brightgreen.svg?style=flat)](http://bioconda.github.io/recipes/raptor/README.html)

```bash
conda install -c bioconda -c conda-forge raptor
```

### Install with brew (Linux, macOS)

```bash
brew install brewsci/bio/raptor
```

### Compile from source
<details><summary>Prerequisites</summary>

* CMake >= 3.8
* GCC 9, 10 or 11 (most recent minor version)
* git

Refer to the [Seqan3 Setup Tutorial](https://docs.seqan.de/seqan/3-master-user/setup.html) for more in depth information.
</details>

<details><summary>Download current master branch</summary>

```bash
git clone --recurse-submodules https://github.com/seqan/raptor
```

</details>

<details><summary>Download specific version</summary>

E.g., for version `1.0.0`:
```bash
git clone --branch raptor-v1.0.0 --recurse-submodules https://github.com/seqan/raptor
```
Or from within an existing repository
```bash
git checkout raptor-v1.0.0
```
</details>

<details><summary>Building</summary>

```bash
cd raptor
mkdir -p build
cd build
cmake ..
make
```

The binary can be found in `bin`.

You may want to add the raptor executable yo your PATH:
```
export PATH=$(pwd)/bin:$PATH
raptor --version
```

</details>

### Example Data and Usage
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

The `bins` folder contains a FASTA file for each bin and the `reads` directory contains a FASTQ file for each bin containing reads from the respective bin (with 2 errors).
Additionally, `mini.fastq` (5 reads of all bins), `all.fastq` (concatenation of all FASTQ files) and `all10.fastq` (`all.fastq` repeated 10 times) are provided in the `reads` folder.

In the following, we will use the `64` data set.
We can now build an index over all the bins:

```
raptor build --kmer 19 --window 23 --size 8m --output index.raptor $(seq -f "example_data/64/bins/bin_%02g.fasta" 0 1 63)
# You can replace `$(seq -f "example_data/64/bins/bin_%02g.fasta" 0 1 63)` by `example_data/64/bins/bin_{00..63}.fasta` if your shell supports this syntax.
# The equivalent command for 1,024 bins is `$(seq -f "example_data/1024/bins/bin_%04g.fasta" 0 1 1023)`
```

You can also prepare a file that contains one file path per line (a line corresponds to a bin) and use this file as input:
```
seq -f "example_data/64/bins/bin_%02g.fasta" 0 1 63 > all_bin_paths.txt
raptor build --kmer 19 --window 23 --size 8m --output another_index.raptor all_bin_paths.txt
```

You may be prompted to enable or disable automatic update notifications. For questions, please consult [the SeqAn documentation](https://github.com/seqan/seqan3/wiki/Update-Notifications).

Afterwards, we can search for all reads from bin 1:

```
raptor search --kmer 19 --window 23 --error 2 --index index.raptor --query example_data/64/reads/mini.fastq --output search.output
```

Each line of the output consists of the read ID (in the toy example these are numbers) and the corresponding bins in which they were found:
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
raptor --help
raptor build --help
raptor search --help
```

#### Preprocessing the input
We offer the option to precompute the minimisers of the input files. This is useful to build indices of big datasets (in the range of several TiB) and also allows an estimation of the needed index size since the amount of minimisers is known.
Following above example, we would change the build step as follows:

First we precompute the minimisers and store them in a directory:
```
mkdir -p precomputed_minimisers
raptor build --kmer 19 --window 23 --size 8m --compute-minimiser --output precomputed_minimisers/ $(seq -f "example_data/64/bins/bin_%02g.fasta" 0 1 63)
```

Then we run the build step again and use the computed minimisers as input:
```
raptor build --kmer 19 --window 23 --size 8m --output minimiser_index.raptor $(seq -f "precomputed_minimisers/bin_%02g.minimiser" 0 1 63)
```

Alternatively, you can also prepare a file that contains one file path per line (a line corresponds to a bin)
and use this file as input for both cases:
```
seq -f "example_data/64/bins/bin_%02g.fasta" 0 1 63 > all_bin_paths.txt
raptor build --kmer 19 --window 23 --size 8m --compute-minimiser --output precomputed_minimisers/ all_bin_paths.txt
seq -f "precomputed_minimisers/bin_%02g.minimiser" 0 1 63 > all_minimiser_paths.txt
raptor build --kmer 19 --window 23 --size 8m --output another_minimiser_index.raptor all_minimiser_paths.txt
```

## Authorship and Copyright
Raptor is being developed by [Enrico Seiler](mailto:enrico.seiler@fu-berlin.de), but also incorporates much work from
other members of [SeqAn](https://www.seqan.de).

### Citation
In your academic works (also comparisons and pipelines) please cite:
  * Seiler, E. et al. (2020). Raptor: A fast and space-efficient pre-filter for querying very large collections of nucleotide sequences. bioRxiv 2020.10.08.330985. doi: https://doi.org/10.1101/2020.10.08.330985

### Supplementary
The subdirectory `util` contains applications and scripts related to the paper.

### License
Raptor is open source software. However, certain conditions apply when you (re-)distribute and/or modify Raptor, please see the [license](https://github.com/seqan/raptor/blob/master/LICENSE.md).
