Mid Project Review
==================

## Current Progress

A website has been made outlining the high-level overview of our project, found [here](https://toshipiazza.github.io/LLVMCFG/). A checklist for
the deliverables for our project include:

- [ ] construct a basic block pass which instruments each conditional branch  
- [ ] write `__not_taken()` and `__taken()` functions for the above instrumentation  
- [ ] build a python script which colors an IDA control flow graph  
- [ ] build a python script which augments IDA control flow for indirect branches  

So far, the basic block pass has been attempted. Currently the pass runs, and is able to
accurately instrument each conditional branch and modify its target and fallthrough
branches. The stdlibc++ functionality has not been written that will be our trampolines
for keeping track of the branches, but is underway. Once these have been completed, the
python scripts will be written augmenting IDA's current funcionality.
