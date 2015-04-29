# FP-Growth-Algorithm

This repo contains the C/C++ implementation of the FP-Growth-Algorithm used for rule mining in (market-basket) dataset. 

<h2> Description </h2>

<h4>main.c</h4> 
<p>
 - this is the driver program. It takes input from the user the dataset, minimum Support (0-100) and minimum confidence (0-1)
</p>
</br>
<h4>FP_TREE_GEN.c</h4>
<p>
- this program makes a pass at the input dataset and first finds the support of each item, removes all the infrequent items from the datasets, sorts each transaction based on decreasing order of the support. After this, a "null" node is created and fp-tree is constructed with th modified data-set. modified dataset "frequent.txt"
</p>
</br>
<h4>FP_GROWTH.cpp</h4>
<p>
- this program takes as input the modified dataset and outputs a file "frequentItemSet.txt" with the frequent k-itemsets.
</p>
</br>
<h4>RULE_MINING.cpp</h4>
<p>
- it takes as input the "frequentItemSet.txt" and generates all possible rules for each itemset, and based on minimumConfidence, it declares whether a rule is valid or not. It outputs the rules found to "generatedRules.txt"
</p>

</br>

