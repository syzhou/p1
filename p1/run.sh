make
./p1Lexe < normal_in.txt > out1
diff out1 normalL_out.txt 
diff normal_save1.txt normal_save1C.txt
diff normal_save2.txt normal_save2C.txt
./p1Lexe < errors_in.txt > out2
diff out2 errors_out.txt 
./p1Lexe < typeahead_in.txt > out3
diff out3 typeahead_out.txt 
