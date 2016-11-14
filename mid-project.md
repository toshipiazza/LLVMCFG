Mid Project Review
==================

## Current Progress

A website has been made outlining the high-level overview of our project, found
[here](https://toshipiazza.github.io/LLVMCFG/). A checklist for the
deliverables for our project include:

- [ ] construct a basic block pass which instruments each conditional branch  
- [ ] write `__not_taken()` and `__taken()` functions for the above
  instrumentation  
- [ ] build a python script which colors an IDA control flow graph  
- [ ] build a python script which augments IDA control flow for indirect
  branches  

So far, the basic block pass has been attempted. Currently the pass runs, and
is able to accurately instrument each conditional branch and modify its target
and fallthrough branches. The stdlibc++ functionality has not been written that
will be our trampolines for keeping track of the branches, but is underway.
Once these have been completed, the python scripts will be written augmenting
IDA's current funcionality.

## Delegation of Work

Toshi will work on the basic block pass. Kevin will construct the `__taken()`
and `__not_taken()` functions into libstdc++. Max will build a python script
that reads in the expected json, and augments IDA's control flow generation
phase.

## Demo of Current Progress

[![asciicast](https://asciinema.org/a/cv66htahirf47836pdal1w7a7.png)](https://asciinema.org/a/cv66htahirf47836pdal1w7a7)

Here, we run our `runpass.sh` script which runs our pass on the test.c file,
which has a conditional. It simply victimizes this conditional and points the
taken branch to `cfg::taken`, and the not-taken branch to `cfg::not_taken`.
Next, we will fill in these stub basic blocks with clean calls which will
notify some global state that a branch has been taken or not.
