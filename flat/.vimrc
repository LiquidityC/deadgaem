"Inform me of lines that are too long
match ErrorMsg '\%>110v.\+'

"GF command sourcefiles
let &path="src,flat/src,"

nnoremap <F1> :Make -j8<cr>
nnoremap <F2> :Make -j8 checkall<cr>
