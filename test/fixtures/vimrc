" vim:foldmethod=marker:foldlevel=0:textwidth=79
"
" I promise to clean up my vimrc one day !
" Kepping up promise made in 9a59c443260aeb6ac64b7766fbe5cc4ad76f860a
" vimrc
" Author: Pratheek
" My Vim settings.
" _____________________
"  Here be my Secrets
" ---------------------
"       o                    / \  //\
"        o    |\___/|      /   \//  \\
"             /0  0  \__  /    //  | \ \
"            /     /  \/_/    //   |  \  \
"            @_^_@'/   \/_   //    |   \   \
"            //_^_/     \/_ //     |    \    \
"         ( //) |        \///      |     \     \
"       ( / /) _|_ /   )  //       |      \     _\
"     ( // /) '/,_ _ _/  ( ; -.    |    _ _\.-~        .-~~~^-.
"   (( / / )) ,-{        _      `-.|.-~-.           .~         `.
"  (( // / ))  '/\      /                 ~-. _ .-~      .-~^-.  \
"  (( /// ))      `.   {            }                   /      \  \
"   (( / ))     .----~-.\        \-'                 .~         \  `. \^-.
"              ///.----..>        \             _ -~             `.  ^-`  ^-_
"                ///-._ _ _ _ _ _ _}^ - - - - ~                     ~-- ,.-~
"
"
" Preamble ---------------------------------------------------------------- {{{

" No explanation needed
set nocompatible

" Load pathogen, and automatically call pathogen#helptags()
execute pathogen#infect()
call pathogen#helptags()
set shell=/bin/bash
"}}}
" Basic settings----------------------------------------------------------- {{{
"
" Better than just /<search term>
" Also, `\v` enables use of Perl compatible regexes
nmap / /\v
syntax on
filetype indent on
filetype plugin on
syntax enable
set background=light

" Have a different colorscheme for GUI and console version of Vim
if has('gui_running')
    colorscheme sol
else
    colorscheme luna-term
endif

" Set stuff (set <whatever>) {{{
" I'm going to try to put a comment above most of these `set` stuff,
" but if its not present, just do a `:h` for that

" Always have a status bar
set laststatus=2
set encoding=utf-8
set t_Co=256
set relativenumber
set autoindent
set smartindent
set incsearch
set listchars=tab:›∙,eol:¬

" Can *NEVER* settle with one font ! :D
" set guifont=Menlo\ for\ Powerline\ 13
set guifont=Monaco\ for\ Powerline\ 13

set hlsearch
set wildmenu
set colorcolumn=80
set cursorline
set tabstop=8
set expandtab
set softtabstop=4
set shiftwidth=4
set foldlevel=99
set foldmethod=indent

" Remember more previously used stuff
set history=1000

" Better term setting (read :h ttyfast for better understanding)
set ttyfast

" Stops screen from redrawing when macros are being executed
set lazyredraw

" NO WRAP ! EVER !
" This is especially usefull for `:vertical h <topic>`
set nowrap

" Amount of time taken to show the matching paren
" (This is in tenths of a sec)
set matchtime=3

" Better completion
" do a `:h 'complete'`
set complete=.,w,b,u,t
" do a `:h 'completeopt'`
set completeopt=longest,menuone,preview,menu

" I think all these guioptions should be in gvimrc,
" but since vimrc loads faster, I've added them here
set guioptions-=T "removes toolbar
set guioptions-=r "removes Right-hand scrollbar
set guioptions-=R "removes Right-hand scrollbar (Which is present in :vsp)
set guioptions-=l "removes Left-hand scrollbar
set guioptions-=L "removes Left-hand scrollbar (which is present in :vsp)
set guioptions-=m "removes menubar

" Defualt Status line
" Commented out all these, in favour of vim-airline
"
" set statusline=
" set statusline+=(%t)
" set statusline+=%m\
" set statusline+=%=\
" set statusline+=%r\
" set statusline+=%{fugitive#statusline()}
" set statusline+=%=\
" set statusline+=%Y\
" set statusline+=(%l/%L)\
" set statusline+=(%p%%)\

" Use the custom fold function
set foldtext=MyFoldText()
"}}}
" Breaking Habit {{{
nnoremap <up> <nop>
nnoremap <down> <nop>
nnoremap <left> <nop>
nnoremap <right> <nop>
inoremap <up> <nop>
inoremap <down> <nop>
inoremap <left> <nop>
inoremap <right> <nop>
vnoremap <up> <nop>
vnoremap <down> <nop>
vnoremap <left> <nop>
vnoremap <right> <nop>
"}}}
" Mind Hacks {{{
" ---------------------------------------------------------------------------
" Better <C-^> hack !
" :nnoremap <C-^> :buffers<CR>:b<Space>
" using tabline (built-in with airline)
nnoremap <C-Tab> :tabnext<CR>
" ---------------------------------------------------------------------------
" with the default `:e` I'll have to remember
" the path of the file (which is hard)
" So, remap `:e` to run `:CtrlPMRUFiles`
" Pros : No need to remember the path, CtrlP will find it for you.
" Cons : Requires CtrlP (dependency) and
"           commands that start with e will be hard to type.
"           (You'll have to hit `:` and wait about a half a sec or so
"           to start typing the command, starting with 'e')
nnoremap :e :CtrlPMRUFiles<CR>
" ---------------------------------------------------------------------------
" clear serached stuff
nnoremap <C-S-c> :let @/=""<CR>
" ---------------------------------------------------------------------------
" Show syntax highlighting groups for word under cursor
" Thanks to Drew Neil from vimcasts
nmap <A-S-P> :call <SID>SynStack()<CR>
function! <SID>SynStack()
  if !exists("*synstack")
    return
  endif
  echo map(synstack(line('.'), col('.')), 'synIDattr(v:val, "name")')
endfunc
" ---------------------------------------------------------------------------
" When using (g)vimdiff (or running `:Gdiff` in fugitive)
" Disable relativenumber and use normal numbers
if &diff
    set norelativenumber
    set number
endif
" ---------------------------------------------------------------------------
" Returns cursor to last position before quitting
augroup line_return
    au!
    au BufReadPost *
        \ if line("'\"") > 0 && line("'\"") <= line("$") |
        \ execute 'normal! g`"zvzz' |
        \ endif
augroup END
" ---------------------------------------------------------------------------
" Key mapping for tab switching
nnoremap <C-t> :tabnew<CR>
" :map <C-x> :tabclose<CR>
" :map <C-h> :tabprevious<CR>
nnoremap <C-Tab> :tabnext<CR>
" ---------------------------------------------------------------------------
" Thanks to Steve Losh
" "Uppercase word" mapping.
"
" This mapping allows you to press <c-u> in insert mode to convert the current
" word to uppercase.  It's handy when you're writing names of constants and
" don't want to use Capslock.
"
" To use it you type the name of the constant in lowercase.  While your
" cursor is at the end of the word, press <c-u> to uppercase it, and then
" continue happily on your way:
"
"                            cursor
"                            v
"     max_connections_allowed|
"     <c-u>
"     MAX_CONNECTIONS_ALLOWED|
"                            ^
"                            cursor
"
" It works by exiting out of insert mode, recording the current cursor location
" in the z mark, using gUiw to uppercase inside the current word, moving
" back to the z mark, and entering insert mode again.
"
" Note that this will overwrite the contents of the z mark.  I never use it,
" but if you do you'll probably want to use another mark.
inoremap <C-u> <esc>mzgUiw`za
" ---------------------------------------------------------------------------
"}}}
" <F5> FileType Runners and Builders {{{
" ---------------------------------------------------------------------------
" Python {{{
augroup ft_python
    au!
    " Run the code in `%` (path/to/file) in python
    " Damn the <leader>r in python-mode for python3
    au Filetype python nnoremap <F5> :<C-u> ! python %<CR>
augroup END
"}}}
" Lua {{{
augroup ft_lua
    au!
    " Run the code in `%` (path/to/file) in lua
    au Filetype lua nnoremap <F5> :<C-u> ! lua %<CR>
augroup END
" }}}
" C {{{
augroup ft_c
    au!
    " Build the given .c file
    " by giving `%` as the arg (which is path/to/file)
    " and store the built binary file in the same path
    "
    " Best explained with example:
    " Let's say file name is foo_bar.c
    " Then, this makes it `:! gcc -Wall foo_bar.c -o foo_bar.c.o`
    " (Slightly bad in naming the bin file ! ;) )
    "
    " This also works in this case.
    " $ gvim ~/foo/bar/baz/dumb.c
    " Then, this runs as:
    " `:!gcc -Wall ~/foo/bar/baz/dumb.c -o ~/foo/bar/baz/dumb.c.o`
    "
    au Filetype c nnoremap <F5> :<C-u> ! gcc -Wall % -o %.o<CR>
augroup END
" }}}
" C++ {{{
augroup ft_cpp
    au!
    " Build the given .cc file
    " by giving `%` as the arg (which is path/to/file)
    " and store the built binary file in the same path
    "
    " Best explained with example:
    " Let's say file name is foo_bar.cc
    " Then, this makes it `:! g++ -Wall foo_bar.cc -o foo_bar.cc.oo`
    " Slightly bad in naming the bin file
    "
    " This also works in this case.
    " $ gvim ~/foo/bar/baz/dumb.cc
    " Then, this runs as:
    " `:!g++ -Wall ~/foo/bar/baz/dumb.cc -o ~/foo/bar/baz/dumb.cc.oo`
    "
    au Filetype cpp nnoremap <F5> :<C-u> ! g++ -Wall % -o %.oo<CR>
augroup END
" }}}
" }}}
" ---------------------------------------------------------------------------
" }}}
" Wild Ignore ------------------------------------------------------------- {{{
set wildignore+=.hg,.git,.svn                    " Version control
set wildignore+=*.aux,*.out,*.toc                " LaTeX intermediate files
set wildignore+=*.jpg,*.bmp,*.gif,*.png,*.jpeg   " binary images
set wildignore+=*.o,*.oo,*.obj,*.exe,*.dll       " compiled object files
set wildignore+=*.spl                            " compiled spelling word lists
set wildignore+=*.sw?                            " Vim swap files
set wildignore+=*.luac                           " Lua byte code
set wildignore+=*.pyc                            " Python byte code
set wildignore+=*.orig                           " Merge resolution files
set wildignore+=$VIMRUNTIME/doc/*.txt            " Individual helpfiles
set wildignore+=$VIMRUNTIME/doc/*.tar.gz         " compressed helpfiles
" For the `**` meaning, do a `:h starstar-wildcard`
set wildignore+=**/doc/*.txt
" Clojure/Leiningen
set wildignore+=classes
set wildignore+=lib
"}}}
" Auto Commands ----------------------------------------------------------- {{{
" General filetype {{{
" ---------------------------------------------------------------------------
" Resize splits when the window is resized
au VimResized * :wincmd =
" First off,  HUGE thanks to Steve Losh !
" Read below !
" Make {<cr> insert a pair of brackets in such a way that the cursor is correctly
" positioned inside of them AND the following code doesn't get unfolded.
au Filetype * inoremap <buffer> {<cr> {}<left><cr><space><space><space><space>.<cr><esc>kA<bs>
" ---------------------------------------------------------------------------
" }}}
" Clojure {{{
" ---------------------------------------------------------------------------
au FileType clojure RainbowParenthesesActivate
au syntax clojure RainbowParenthesesLoadRound
au syntax clojure RainbowParenthesesLoadSquare
au syntax clojure RainbowParenthesesLoadBraces
" ---------------------------------------------------------------------------
" }}}
" Python {{{
" ---------------------------------------------------------------------------
autocmd BufWritePre *.py normal m`:%s/\s\+$//e ``
autocmd BufRead *.py set smartindent cinwords=if,elif,else,for,while,try,except,finally,def,class
au FileType python set omnifunc=pythoncomplete#Complete
au FileType python syn keyword pythonDecorator True None False self
" ---------------------------------------------------------------------------
" }}}
" }}}
" Custom Functions -------------------------------------------------------- {{{
" ---------------------------------------------------------------------------
function! MyFoldText() " {{{
    let line = getline(v:foldstart)

    let nucolwidth = &fdc + &number * &numberwidth
    let windowwidth = winwidth(0) - nucolwidth - 3
    let foldedlinecount = v:foldend - v:foldstart

    " expand tabs into spaces
    let onetab = strpart('          ', 0, &tabstop)
    let line = substitute(line, '\t', onetab, 'g')

    let line = strpart(line, 0, windowwidth - 2 -len(foldedlinecount))
    let fillcharcount = windowwidth - len(line) - len(foldedlinecount)
    return line . ' (' . foldedlinecount . ') ' . '…' . repeat(" ",fillcharcount) .  ' '
endfunction " }}}
" Nyan cat
command! NyanMe call NyanMe()
" ---------------------------------------------------------------------------
function! NyanMe() " {{{
    hi NyanFur guifg=#BBBBBB
    hi NyanPoptartEdge guifg=#ffd0ac
    hi NyanPoptartFrosting guifg=#fd3699 guibg=#fe98ff
    hi NyanRainbow1 guifg=#6831f8
    hi NyanRainbow2 guifg=#0099fc
    hi NyanRainbow3 guifg=#3cfa04
    hi NyanRainbow4 guifg=#fdfe00
    hi NyanRainbow5 guifg=#fc9d00
    hi NyanRainbow6 guifg=#fe0000


    echohl NyanRainbow1
    echon "≈"
    echohl NyanRainbow2
    echon "≋"
    echohl NyanRainbow3
    echon "≈"
    echohl NyanRainbow4
    echon "≋"
    echohl NyanRainbow5
    echon "≈"
    echohl NyanRainbow6
    echon "≋"
    echohl NyanRainbow1
    echon "≈"
    echohl NyanRainbow2
    echon "≋"
    echohl NyanRainbow3
    echon "≈"
    echohl NyanRainbow4
    echon "≋"
    echohl NyanRainbow5
    echon "≈"
    echohl NyanRainbow6
    echon "≋"
    echohl None
    echo ""

    echohl NyanRainbow1
    echon "≈"
    echohl NyanRainbow2
    echon "≋"
    echohl NyanRainbow3
    echon "≈"
    echohl NyanRainbow4
    echon "≋"
    echohl NyanRainbow5
    echon "≈"
    echohl NyanRainbow6
    echon "≋"
    echohl NyanRainbow1
    echon "≈"
    echohl NyanRainbow2
    echon "≋"
    echohl NyanRainbow3
    echon "≈"
    echohl NyanRainbow4
    echon "≋"
    echohl NyanRainbow5
    echon "≈"
    echohl NyanRainbow6
    echon "≋"
    echohl NyanFur
    echon "╰"
    echohl NyanPoptartEdge
    echon "⟨"
    echohl NyanPoptartFrosting
    echon "⣮⣯⡿"
    echohl NyanPoptartEdge
    echon "⟩"
    echohl NyanFur
    echon "⩾^ω^⩽"
    echohl None
    echo ""

    echohl NyanRainbow1
    echon "≈"
    echohl NyanRainbow2
    echon "≋"
    echohl NyanRainbow3
    echon "≈"
    echohl NyanRainbow4
    echon "≋"
    echohl NyanRainbow5
    echon "≈"
    echohl NyanRainbow6
    echon "≋"
    echohl NyanRainbow1
    echon "≈"
    echohl NyanRainbow2
    echon "≋"
    echohl NyanRainbow3
    echon "≈"
    echohl NyanRainbow4
    echon "≋"
    echohl NyanRainbow5
    echon "≈"
    echohl NyanRainbow6
    echon "≋"
    echohl None
    echon " "
    echohl NyanFur
    echon "” ‟"
    echohl None

    sleep 1
    redraw
    echo " "
    echo " "
    echo "Noms?"
    redraw
endfunction " }}}
" }}}
" Plugin Settings --------------------------------------------------------- {{{
" Airline {{{
let g:airline_theme = 'sol'
let g:airline_left_sep=''
let g:airline_left_alt_sep='|'
let g:airline_right_sep=''
let g:airline_right_alt_sep='|'
let g:airline_powerline_fonts = 1
let g:airline#extensions#tabline#enabled = 1
let g:airline#extensions#tabline#fnamemod = ':~:.'
" let g:airline#extensions#tabline#fnamemod = ':t:~'
" let g:airline#extensions#tabline#fnamemod = ':p:~'

" Get rid of the arrows in tabline
let g:airline#extensions#tabline#left_sep = ' '
let g:airline#extensions#tabline#left_alt_sep = '|'

" Enable Fugitive support in airline
let g:airline#extensions#branch#enabled = 1

" Show hunks, only if there is change in file,
" with respect to the version last commited into git
let g:airline#extensions#hunks#non_zero_only = 1

" Display buffers in a single tab
" (also this is required for the next setting)
let g:airline#extensions#tabline#show_buffers = 1

" Show tabline only if more than 2 buffers exist
let g:airline#extensions#tabline#buffer_min_count = 2

" unicode symbols
let g:airline_branch_prefix = 'Br:'
let g:airline_paste_symbol = 'ρ'

" Reducing mode strings to a single chars
let g:airline_mode_map = {
    \ '__' : '-',
    \ 'n'  : 'N',
    \ 'i'  : 'I',
    \ 'R'  : 'R',
    \ 'c'  : 'C',
    \ 'v'  : 'V',
    \ 'V'  : 'V',
    \ '' : 'V',
    \ 's'  : 'S',
    \ 'S'  : 'S',
    \ '' : 'S',
    \ }

" Custom Function to display a slightly modified airline
" Slight change to show branch info on the right side
" rather than next to the hunks
function! AirlineInit()
    let g:airline_section_a = airline#section#create(['mode'])
    let g:airline_section_b = airline#section#create_left(['hunks'])
    let g:airline_section_c = airline#section#create(['%f'])
    let g:airline_section_y = airline#section#create_right(['branch', 'ffenc'])
endfunction
autocmd VimEnter * call AirlineInit()
" }}}
" Startify {{{

let g:startify_bookmarks = [
            \ '~/.vim/vimrc',
            \ ]
let g:startify_files_number = 8
let g:startify_change_to_dir = 0
let g:startify_change_to_vcs_root = 1
let g:startify_skiplist = [
                \ '.git/COMMIT_EDITMSG',
                \ '.gtkrc-2.0',
                \ '/usr/share/vim/vim74/doc',
                \ '/etc/*',
                \ $VIMRUNTIME . '*/doc',
                \ 'bundle/.*/doc'
                \ ]

let g:startify_list_order = [
      \ ['   MRU:'],
      \ 'files',
      \ ['   Sess:'],
      \ 'sessions',
      \ ['   Markers:'],
      \ 'bookmarks'
      \ ]
" Startify Custom Header
"let g:startify_custom_header = [
            "\ '  .____---^^     ^^---____.                                                      ',
            "\ '  TI      *       *      IT  Three Rings for the Elvin-Kings under the sky.      ',
            "\ '  !I          *          I!  Seven for the DwarfLords in their halls of stone.   ',
            "\ '   X                     X       Nine for the Mortal Men doomed to die.          ',
            "\ '   XL                   JX       One for the Dark Lord on his dark throne.       ',
            "\ '   II        / \        II   In the Land of Mordor where the Shadow Lies.        ',
            "\ '   II   / \ /   \ / \   II                                                       ',
            "\ '    X  /   v     v   \  X       One Ring to rule them all,One Ring to find them, ',
            "\ '    ``/    _     _    \''     One Ring to bring them all and in the Darkness     ',
            "\ '     \\- _-_ -_- _-_ -//         Bind Them                                       ',
            "\ '       \\_-  -_-  -_//          In the Land of Mordor where the Shadows Lie.     ',
            "\ '         ``       ''                                                             ',
            "\ '           ``-_-''                                                               ',
            "\ '                                                    "Lord Of THe Rings"          ',
            "\ '                                                          by J.R.R. Tolkien      ',
            "\ '',
            "\ ]
" }}}
" CtrlP {{{

" make CtrlP exclude these type of files from adding to MRUFiles cache
let g:ctrlp_mruf_exclude = '*.tar.gz\|'
let g:ctrlp_clear_cache_on_exit = 1
let g:ctrlp_cache_dir = $HOME.'/.cache/ctrlp'
" }}}
" SuperTab {{{

" let g:SuperTabDefaultCompletionType = \"<c-p>"
let g:SuperTabDefaultCompletionType = "<c-n>"
let g:SuperTabLongestHighlight = 1
let g:SuperTabCrMapping = 1
" }}}
" Indent Guides {{{

let g:indent_guides_guide_size = 1
" let g:indent_guides_enable_on_vim_startup = 1
" }}}
" ---------------------------------------------------------------------------
"}}}
"
