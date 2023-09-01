![](https://drive.google.com/uc?id=1iU6fzWHAfoWgrfuJr0rPQp3K499JxbeE)
A command-line tool for comparing binary files, pinpointing differences down to the byte level. Features address range exemption for focused comparisons. Ideal for developers and analysts.

## Usage
Arguments:
- Path to file 1 (mandatory)
- Path to file 2 (mandatory)
- Address ranges to skip searching (optional)

Example:
`BinCompare.exe "path_to_file1.bin" "path_to_file2.bin" 0x3907-0x4D96 0xE859D-0xEBBFB`

## Preview
![Preview of programs current output](https://drive.google.com/uc?id=19309uMdOwsheXRKaCBGksVhN6e7o0neL)

## TODO
- verbose arg for more detailed output
- arg error checking
- nocolor arg for any unsupported CLI
- probably some other stuff
