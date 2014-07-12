set number
set shiftwidth=4
language messages zh_CN.utf-8   
set completeopt=longest,menu    
set fileencodings=utf-8,gb18030,ucs-bom,gbk,gb2312,cp936   
"set expandtab
map <C-B> :call CompileRunCpp()<CR>
map <F6> <esc>ggVG " +y 
map <F3> <esc>gg=G " format C/C++
func! CompileRunCpp()
se"w"
if &filetype == 'c'
     exec "!g++ % -o %< -L/usr/include/mysql -lmysqlclient"
	 exec "! ./%<"
elseif &filetype == 'cpp'
	 exec "!g++ % -o %<"
     exec "!time ./%<"    
elseif &filetype == 'java' 
	 exec "!javac %" 
	 exec "!time java %<"
elseif &filetype == 'sh'
	 exec "!/bin/bash %"
elseif &filetype == 'python'|| &filetype == 'py'
	exec "!time python2.7 %"
elseif &filetype == 'html'
    exec "!google-chrome %&"
endif

endfunc

map<C-k> :s/\/\///g<CR> k<C-^>

map<C-l> :s/^/\/\//g<CR><CR>

map<C-e> :! /bin/bash<CR>
set autoindent
set cindent  
set tabstop=4 
set smartindent
set showmatch
set nobackup
set noswapfile
set autowrite
colorscheme evening "freya
:inoremap ( ()<ESC>i
		:inoremap ) <c-r>=ClosePair(')')<CR>
:inoremap { {<CR>}<ESC>O
	:inoremap } <c-r>=ClosePair('}')<CR>
	:inoremap [ []<ESC>i
	:inoremap ] <c-r>=ClosePair(']')<CR>
	function! ClosePair(char)
	    if getline('.')[col('.') - 1] == a:char
	            return "\<Right>"
		        else
			        return a:char
				    endif
				    endfunction
map<F2> :call SetTitle()<CR>
func SetTitle()
let l = 0
let l = l + 1 | call setline(l,'#include <sys/types.h>')
let l = l + 1 | call setline(l,'#include <sys/stat.h>')
let l = l + 1 | call setline(l,'#include <unistd.h>')
let l = l + 1 | call setline(l,'#include <stdio.h>')
let l = l + 1 | call setline(l,'#include <string.h>')
let l = l + 1 | call setline(l,'#include <fcntl.h>')
let l = l + 1 | call setline(l,'#include <math.h>')
let l = l + 1 | call setline(l,'#include <stdlib.h>')
let l = l + 1 | call setline(l,'')
let l = l + 1 | call setline(l,'int main()')
let l = l + 1 | call setline(l,'{')
let l = l + 1 | call setline(l,'    ')
let l = l + 1 | call setline(l,'    return 0;')
let l = l + 1 | call setline(l,'}')
endfunc
