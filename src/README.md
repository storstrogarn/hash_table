
# Dokumentation

## Köra och kompilera programmet
Vi har valt att göra en make-fil i vårt program, så vi kompilerar genom att köra make, följt av namnet på filen vi vill kompilera. Vi kan också köra tester, och minnesläckagetester, med liknande typ av syntax. Alla tester och minnestester körs på samma sätt; make följt av ett namn, det vill säga första delen av .c-filens namn; hash, linked, iterator, följt av _tests eller _mem_tests för alla tre. Men för att endast kompilera .c-filen, det vill säga inte testerna så ska man skriva make följt av .c-filens namn. Men dessa make-kommandon kommer att klaga på att main är odefinierad vilket är på grund av att vi i regel använder test-filens main-funktion.
Exempelvis:
```

make hash_table
make hash_tests
make hash_mem_test

```

Vi kan också köra alla tester, eller köra alla minnestester samtidigt.  
Så här:

```

make test
make mem_test

```

Om vi vill testa vårt hashtable kan vi använda freq för att göra det. Dessa tester omfattas inte av make-test eftersom vi måste specificera vad vi vill köra det på. Freq-programmet plockar ut ord ur en textfil och räknar dem. För närvarande kan vi köra 3 olika exempelfiler. Vi har skapat tester för dessa men det går att köra freq på vilken fil som helst så länge den har rätt format och är tillgänglig för freq.

Så här:

```

make freq
./freq ./small.txt
./freq ./10k-words.txt
./freq ./16k-words.txt
./freq ./insert_file_name_here.txt

```
Om man vill ta bort alla sina .exe-filer kan man göra det med clear.  
Så här:

```

make clear

```
	
## Design decisions 

* ioopm_hash_table_lookup returnerar sitt resultat i en option-struct, där “resultat.success” indikerar om det var en framgång och “resultat.value” innehåller det hittade värdet om det hittades.

* ioopm_hash_table_create tar emot en hashfunktion som argument så att den kan användas internt i andra funktioner.

* ioopm_hash_table_remove returnerar värdet som den tog bort och om inget värde hittades kommer den att returnera ett elem_t med värdet “NO”.

* ioopm_hash_table_has_value tar emot en jämförelsefunktion; en ioopm_eq_function för elem_t-unioner, vilket den gör på grund av att den måste kolla igenom hela hashtable:ts värden och jämföra dem med inputvärdet.

* I ioopm_linked_list_create skickar vi in en jämförelsefunktion för elem_t:s; en ioopm_eq_function för att kunna lätt kunna jämföra elem_ts med varandra vid behov. 



## Error handling

I diverse funktioner används assert för att kontrollera att en funktionsparameter är giltig, till exempel i ioopm_linked_list_insert så används två stycken assertanrop för att kontrollera att indexet som har matats in är giltigt.  
Vi använder också många interna checkar i form av if- eller while-satser för att fånga upp alla fall. Till exempel om vi ska avsluta en loop så använder vi break för att inte köra den något mer, , särskilt i fall då loop:ens fortsättning kan orsaka problem.




# Initial Profiling Results

For each input, what are the top 3 functions?
-----------------------------------------------------------------------------------------------------------------
Before resize:
```

For small:
  time   seconds   seconds    calls  Ts/call  Ts/call  name    
  0.00      0.00     0.00      216     0.00     0.00  string_sum_hash
  0.00      0.00     0.00       81     0.00     0.00  find_previous_entry_for_key
  0.00      0.00     0.00       54     0.00     0.00  ioopm_hash_table_lookup

For 10k
 time   seconds   seconds    calls  ms/call  ms/call  name    
100.17      0.01     0.01    30000     0.00     0.00  find_previous_entry_for_key
  0.00      0.01     0.00   217253     0.00     0.00  string_sum_hash
  0.00      0.01     0.00    20000     0.00     0.00  ioopm_hash_table_lookup

For 16k:
Each sample counts as 0.01 seconds       
 time   seconds   seconds    calls  ms/call  ms/call  name    
 66.78      0.06     0.06  1201439     0.00     0.00  string_sum_hash
 22.26      0.08     0.02    50976     0.00     0.00  find_previous_entry_for_key
 11.13      0.09     0.01        1    10.02    87.96  process_file

```
After resize:
```

For small:  
 time   seconds   seconds    calls  Ts/call  Ts/call  name    
  0.00      0.00     0.00      282     0.00     0.00  ioopm_hash_table_size
  0.00      0.00     0.00      276     0.00     0.00  ioopm_hash_table_is_empty
  0.00      0.00     0.00      183     0.00     0.00  string_sum_hash
For 10k:
 time   seconds   seconds    calls  ms/call  ms/call  name    
100.14      0.01     0.01    20000     0.00     0.00  ioopm_hash_table_lookup
  0.00      0.01     0.00    90570     0.00     0.00  string_sum_hash
  0.00      0.01     0.00    30252     0.00     0.00  find_previous_entry_for_key

For 16k:
Each sample counts as 0.01 seconds       
 time   seconds   seconds    calls  ms/call  ms/call  name    
 58.41      0.14     0.14     5483     0.03     0.03  ioopm_linked_list_get
 22.95      0.20     0.06   150626     0.00     0.00  string_sum_hash
 10.43      0.22     0.03        1    25.03   193.23  process_file
 
 ```
For each input, what are the top 3 functions in your code (that you have written), or is it library functions?
-----------------------------------------------------------------------------------------------------------------
For small: We wrote  find_previous_entry_for_key and ioopm_hash_table_lookup, string_sum_hash was provided to us but is not a library function!  
For 10k: We wrote  find_previous_entry_for_key and ioopm_hash_table_lookup, string_sum_hash was provided to us but is not a library function!  
For 16k: We wrote  find_previous_entry_for_key. String_sum_hash, and process_file  was provided to us but is not a library function!  
 
Are the top 3 functions in your code consistent across the inputs? Why? Why not?
-----------------------------------------------------------------------------------------------------------------
No they are not, for 16k the process_file takes the the third spot, this is due to it appearing to have a exponential time complexity (n^2).

Is there some kind of trend? (Possibly several.)
-----------------------------------------------------------------------------------------------------------------
The bigger the file, the bigger the time consumption for process_file.
Another trend we can see is that find_previous_entry takes up a lot more time then when we only have a few words in.


Do the results correspond with your expectations?
-----------------------------------------------------------------------------------------------------------------
We feel that without going to deep the results we are getting is fairly reasonable!
 
Based on these results, do you see a way to make your program go faster?
-----------------------------------------------------------------------------------------------------------------
Disregarding stringhash_sum then the most significant change would be made in find_previous_entry. Improving its runtime would certainly improve the overall program's runtime as well. Though any immediate solutions to this is not apparent to us.


## Solution to global warming
[here](https://www.youtube.com/watch?v=dQw4w9WgXcQ)
 
