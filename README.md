# squeeze
Simple Huffman File Compressor, Unix filter.

    compress:
    $ tar c foo/ | squeeze -c > foo.tar.sq

    decompress:
    $ cat foo.tar.sq | squeeze -x | tar xv

that's it.

You can inspect the huffman tree with `writetree`.
