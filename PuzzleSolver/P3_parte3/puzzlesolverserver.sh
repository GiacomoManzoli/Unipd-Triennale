#!/bin/bash
cd bin
rmiregistry &
echo "RMIRegistry avviato"
java PuzzleServer.PuzzleSolverServer $@
cd ..

