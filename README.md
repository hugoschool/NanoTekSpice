# NanoTekSpice

According to the subject (./G-OOP-400_nanotekspice.pdf):
> NanoTekSpice is a logic simulator that builds a graph (the nodes of which will be simulated digital electronic components, inputs or outputs) from a configuration file, and injects values into that graph to get results.

## Build

```sh
make -j`nproc`
./nanotekspice file.nts
```

Lots of NTS files are available in the subject/nts_single folder.

## Documentation

The architecture is available at docs/ARCHITECTURE.md.

It is made using [Mermaid](https://mermaid.js.org/).
