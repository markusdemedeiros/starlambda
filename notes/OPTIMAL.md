## Notes on John Lamping's "An Algorithm for Optimal Lambda Calulus Reduction"

*Goal:* Take as long as you need to fully understand this paper and prepare to implement it

- Problem: Duplicate terms are inefficient. 
- Levy's Labelling: Two links have the same label if their origin is common.
- Optimality: All copies of a redex are reduced in one step. Levy gives no implementation.
- This algorithm uses graph rewrite rules. Order does not matter except for efficincy. 
- The algorithm avoids copying but does not merge identical substructures. 
- Strategy: Get acquainted with a simpler algorithm, and fix the issues with the full one. 


### Simplified Execution
- Notation: Application nodes `@`, lambda nodes `\x`, variable nodes `x`, fan nodes `x∇o` and `xΔo`. 
- Thick lines are the next step.
- We assume one variable per lambda (in all rules or just this one?); makes the rule connected. 
- Branches on fan-out nodes follow the same `x` or `o` path
- The simplified algorithm does not care for the correct pairing of fan nodes
- Nodes do not duplicate unless they represent different work

### Execution
- The issue is that the accumulated context must both track which paths have been taken, and which fan-outs pair with which fan in's.
- Labelling is insufficient due to looping paths
- Introduce bracket nodes `U`, `n`
- Traversals of fans from different enclosures do not pair
- Without intervening brackets, pairs of identically labelled fans match. 
