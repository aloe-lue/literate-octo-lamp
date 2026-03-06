let SessionLoad = 1
if &cp | set nocp | endif
let s:cpo_save=&cpo
set cpo&vim
map! <S-Insert> <MiddleMouse>
imap <silent> <C-Y>m <Plug>(emmet-merge-lines)
inoremap <Plug>(emmet-merge-lines) =emmet#util#closePopup()=emmet#mergeLines()
imap <silent> <C-Y>A <Plug>(emmet-anchorize-summary)
inoremap <Plug>(emmet-anchorize-summary) =emmet#util#closePopup()=emmet#anchorizeURL(1)
imap <silent> <C-Y>a <Plug>(emmet-anchorize-url)
inoremap <Plug>(emmet-anchorize-url) =emmet#util#closePopup()=emmet#anchorizeURL(0)
imap <silent> <C-Y>k <Plug>(emmet-remove-tag)
inoremap <Plug>(emmet-remove-tag) =emmet#util#closePopup()=emmet#removeTag()
imap <silent> <C-Y>j <Plug>(emmet-split-join-tag)
inoremap <Plug>(emmet-split-join-tag) :call emmet#splitJoinTag()
imap <silent> <C-Y>/ <Plug>(emmet-toggle-comment)
inoremap <Plug>(emmet-toggle-comment) =emmet#util#closePopup()=emmet#toggleComment()
imap <silent> <C-Y>I <Plug>(emmet-image-encode)
inoremap <Plug>(emmet-image-encode) =emmet#util#closePopup()=emmet#imageEncode()
imap <silent> <C-Y>i <Plug>(emmet-image-size)
inoremap <Plug>(emmet-image-size) =emmet#util#closePopup()=emmet#imageSize()
inoremap <Plug>(emmet-move-prev-item) :call emmet#moveNextPrevItem(1)
inoremap <Plug>(emmet-move-next-item) :call emmet#moveNextPrevItem(0)
imap <silent> <C-Y>N <Plug>(emmet-move-prev)
inoremap <Plug>(emmet-move-prev) =emmet#util#closePopup()=emmet#moveNextPrev(1)
imap <silent> <C-Y>n <Plug>(emmet-move-next)
inoremap <Plug>(emmet-move-next) =emmet#util#closePopup()=emmet#moveNextPrev(0)
imap <silent> <C-Y>D <Plug>(emmet-balance-tag-outword)
inoremap <Plug>(emmet-balance-tag-outword) :call emmet#balanceTag(-1)
imap <silent> <C-Y>d <Plug>(emmet-balance-tag-inward)
inoremap <Plug>(emmet-balance-tag-inward) :call emmet#balanceTag(1)
imap <silent> <C-Y>u <Plug>(emmet-update-tag)
inoremap <Plug>(emmet-update-tag) =emmet#util#closePopup()=emmet#updateTag()
imap <silent> <C-Y>; <Plug>(emmet-expand-word)
inoremap <Plug>(emmet-expand-word) =emmet#util#closePopup()=emmet#expandAbbr(1,"")
imap <silent> <C-Y>, <Plug>(emmet-expand-abbr)
inoremap <Plug>(emmet-expand-abbr) =emmet#util#closePopup()=emmet#expandAbbr(0,"")
imap <C-G>S <Plug>ISurround
imap <C-G>s <Plug>Isurround
imap <C-S> <Plug>Isurround
inoremap <silent> <Plug>(ale_complete) :ALEComplete
inoremap <C-U> u
map <silent>  :call ReadMan()
vmap <silent> c <Plug>(emmet-code-pretty)
nmap <silent> m <Plug>(emmet-merge-lines)
nmap <silent> A <Plug>(emmet-anchorize-summary)
nmap <silent> a <Plug>(emmet-anchorize-url)
nmap <silent> k <Plug>(emmet-remove-tag)
nmap <silent> j <Plug>(emmet-split-join-tag)
nmap <silent> / <Plug>(emmet-toggle-comment)
nmap <silent> I <Plug>(emmet-image-encode)
nmap <silent> i <Plug>(emmet-image-size)
nmap <silent> N <Plug>(emmet-move-prev)
nmap <silent> n <Plug>(emmet-move-next)
vmap <silent> D <Plug>(emmet-balance-tag-outword)
nmap <silent> D <Plug>(emmet-balance-tag-outword)
vmap <silent> d <Plug>(emmet-balance-tag-inward)
nmap <silent> d <Plug>(emmet-balance-tag-inward)
nmap <silent> u <Plug>(emmet-update-tag)
nmap <silent> ; <Plug>(emmet-expand-word)
vmap <silent> , <Plug>(emmet-expand-abbr)
nmap <silent> , <Plug>(emmet-expand-abbr)
vmap ,gq :s/\s\+/ /ggvgq
nmap ,gq :%s/\s\+/ /ggq1G
map Q gq
xmap S <Plug>VSurround
nmap \p <Plug>(Prettier)
vmap _j :call Justify('tw',4)
nmap _j :%call Justify('tw',4)
nmap cS <Plug>CSurround
nmap cs <Plug>Csurround
nmap ds <Plug>Dsurround
xmap gx <Plug>NetrwBrowseXVis
nmap gx <Plug>NetrwBrowseX
xmap gS <Plug>VgSurround
nmap ySS <Plug>YSsurround
nmap ySs <Plug>YSsurround
nmap yss <Plug>Yssurround
nmap yS <Plug>YSurround
nmap ys <Plug>Ysurround
nnoremap <SNR>155_: :=v:count ? v:count : ''
nnoremap <SNR>161_: :=v:count ? v:count : ''
nnoremap <SNR>148_: :=v:count ? v:count : ''
nnoremap <SNR>133_: :=v:count ? v:count : ''
nnoremap <SNR>149_: :=v:count ? v:count : ''
nnoremap <SNR>152_: :=v:count ? v:count : ''
nnoremap <SNR>153_: :=v:count ? v:count : ''
map <S-Insert> <MiddleMouse>
nnoremap <SNR>147_: :=v:count ? v:count : ''
xnoremap <silent> <Plug>NetrwBrowseXVis :call netrw#BrowseXVis()
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#BrowseX(netrw#GX(),netrw#CheckIfRemote(netrw#GX()))
nnoremap <silent> <Plug>GitGutterPreviewHunk :call gitgutter#utility#warn('Please change your map <Plug>GitGutterPreviewHunk to <Plug>(GitGutterPreviewHunk)')
nnoremap <silent> <Plug>(GitGutterPreviewHunk) :GitGutterPreviewHunk
nnoremap <silent> <Plug>GitGutterUndoHunk :call gitgutter#utility#warn('Please change your map <Plug>GitGutterUndoHunk to <Plug>(GitGutterUndoHunk)')
nnoremap <silent> <Plug>(GitGutterUndoHunk) :GitGutterUndoHunk
nnoremap <silent> <Plug>GitGutterStageHunk :call gitgutter#utility#warn('Please change your map <Plug>GitGutterStageHunk to <Plug>(GitGutterStageHunk)')
nnoremap <silent> <Plug>(GitGutterStageHunk) :GitGutterStageHunk
xnoremap <silent> <Plug>GitGutterStageHunk :call gitgutter#utility#warn('Please change your map <Plug>GitGutterStageHunk to <Plug>(GitGutterStageHunk)')
xnoremap <silent> <Plug>(GitGutterStageHunk) :GitGutterStageHunk
nnoremap <silent> <expr> <Plug>GitGutterPrevHunk &diff ? '[c' : ":\call gitgutter#utility#warn('Please change your map \<Plug>GitGutterPrevHunk to \<Plug>(GitGutterPrevHunk)')\"
nnoremap <silent> <expr> <Plug>(GitGutterPrevHunk) &diff ? '[c' : ":\execute v:count1 . 'GitGutterPrevHunk'\"
nnoremap <silent> <expr> <Plug>GitGutterNextHunk &diff ? ']c' : ":\call gitgutter#utility#warn('Please change your map \<Plug>GitGutterNextHunk to \<Plug>(GitGutterNextHunk)')\"
nnoremap <silent> <expr> <Plug>(GitGutterNextHunk) &diff ? ']c' : ":\execute v:count1 . 'GitGutterNextHunk'\"
xnoremap <silent> <Plug>(GitGutterTextObjectOuterVisual) :call gitgutter#hunk#text_object(0)
xnoremap <silent> <Plug>(GitGutterTextObjectInnerVisual) :call gitgutter#hunk#text_object(1)
onoremap <silent> <Plug>(GitGutterTextObjectOuterPending) :call gitgutter#hunk#text_object(0)
onoremap <silent> <Plug>(GitGutterTextObjectInnerPending) :call gitgutter#hunk#text_object(1)
vmap <silent> <C-Y>c <Plug>(emmet-code-pretty)
vnoremap <Plug>(emmet-code-pretty) :call emmet#codePretty()
nmap <silent> <C-Y>m <Plug>(emmet-merge-lines)
nnoremap <Plug>(emmet-merge-lines) :call emmet#mergeLines()
nmap <silent> <C-Y>A <Plug>(emmet-anchorize-summary)
nnoremap <Plug>(emmet-anchorize-summary) :call emmet#anchorizeURL(1)
nmap <silent> <C-Y>a <Plug>(emmet-anchorize-url)
nnoremap <Plug>(emmet-anchorize-url) :call emmet#anchorizeURL(0)
nmap <silent> <C-Y>k <Plug>(emmet-remove-tag)
nnoremap <Plug>(emmet-remove-tag) :call emmet#removeTag()
nmap <silent> <C-Y>j <Plug>(emmet-split-join-tag)
nnoremap <Plug>(emmet-split-join-tag) :call emmet#splitJoinTag()
nmap <silent> <C-Y>/ <Plug>(emmet-toggle-comment)
nnoremap <Plug>(emmet-toggle-comment) :call emmet#toggleComment()
nmap <silent> <C-Y>I <Plug>(emmet-image-encode)
nnoremap <Plug>(emmet-image-encode) :call emmet#imageEncode()
nmap <silent> <C-Y>i <Plug>(emmet-image-size)
nnoremap <Plug>(emmet-image-size) :call emmet#imageSize()
nnoremap <Plug>(emmet-move-prev-item) :call emmet#moveNextPrevItem(1)
nnoremap <Plug>(emmet-move-next-item) :call emmet#moveNextPrevItem(0)
nmap <silent> <C-Y>N <Plug>(emmet-move-prev)
nnoremap <Plug>(emmet-move-prev) :call emmet#moveNextPrev(1)
nmap <silent> <C-Y>n <Plug>(emmet-move-next)
nnoremap <Plug>(emmet-move-next) :call emmet#moveNextPrev(0)
vmap <silent> <C-Y>D <Plug>(emmet-balance-tag-outword)
vnoremap <Plug>(emmet-balance-tag-outword) :call emmet#balanceTag(-1)
nmap <silent> <C-Y>D <Plug>(emmet-balance-tag-outword)
nnoremap <Plug>(emmet-balance-tag-outword) :call emmet#balanceTag(-1)
vmap <silent> <C-Y>d <Plug>(emmet-balance-tag-inward)
vnoremap <Plug>(emmet-balance-tag-inward) :call emmet#balanceTag(1)
nmap <silent> <C-Y>d <Plug>(emmet-balance-tag-inward)
nnoremap <Plug>(emmet-balance-tag-inward) :call emmet#balanceTag(1)
nmap <silent> <C-Y>u <Plug>(emmet-update-tag)
nnoremap <Plug>(emmet-update-tag) :call emmet#updateTag()
nmap <silent> <C-Y>; <Plug>(emmet-expand-word)
nnoremap <Plug>(emmet-expand-word) :call emmet#expandAbbr(1,"")
vmap <silent> <C-Y>, <Plug>(emmet-expand-abbr)
vnoremap <Plug>(emmet-expand-abbr) :call emmet#expandAbbr(2,"")
nmap <silent> <C-Y>, <Plug>(emmet-expand-abbr)
nnoremap <Plug>(emmet-expand-abbr) :call emmet#expandAbbr(3,"")
nnoremap <silent> <Plug>SurroundRepeat .
nnoremap <silent> <Plug>(ale_info_preview) :ALEInfo -preview
nnoremap <silent> <Plug>(ale_info_clipboard) :ALEInfo -clipboard
nnoremap <silent> <Plug>(ale_info_echo) :ALEInfo -echo
nnoremap <silent> <Plug>(ale_info) :ALEInfo
nnoremap <silent> <Plug>(ale_repeat_selection) :ALERepeatSelection
nnoremap <silent> <Plug>(ale_code_action) :ALECodeAction
nnoremap <silent> <Plug>(ale_filerename) :ALEFileRename
nnoremap <silent> <Plug>(ale_rename) :ALERename
nnoremap <silent> <Plug>(ale_import) :ALEImport
nnoremap <silent> <Plug>(ale_documentation) :ALEDocumentation
nnoremap <silent> <Plug>(ale_hover) :ALEHover
nnoremap <silent> <Plug>(ale_find_references) :ALEFindReferences
nnoremap <silent> <Plug>(ale_go_to_implementation_in_vsplit) :ALEGoToImplementation -vsplit
nnoremap <silent> <Plug>(ale_go_to_implementation_in_split) :ALEGoToImplementation -split
nnoremap <silent> <Plug>(ale_go_to_implementation_in_tab) :ALEGoToImplementation -tab
nnoremap <silent> <Plug>(ale_go_to_implementation) :ALEGoToImplementation
nnoremap <silent> <Plug>(ale_go_to_type_definition_in_vsplit) :ALEGoToTypeDefinition -vsplit
nnoremap <silent> <Plug>(ale_go_to_type_definition_in_split) :ALEGoToTypeDefinition -split
nnoremap <silent> <Plug>(ale_go_to_type_definition_in_tab) :ALEGoToTypeDefinition -tab
nnoremap <silent> <Plug>(ale_go_to_type_definition) :ALEGoToTypeDefinition
nnoremap <silent> <Plug>(ale_go_to_definition_in_vsplit) :ALEGoToDefinition -vsplit
nnoremap <silent> <Plug>(ale_go_to_definition_in_split) :ALEGoToDefinition -split
nnoremap <silent> <Plug>(ale_go_to_definition_in_tab) :ALEGoToDefinition -tab
nnoremap <silent> <Plug>(ale_go_to_definition) :ALEGoToDefinition
nnoremap <silent> <Plug>(ale_fix) :ALEFix
nnoremap <silent> <Plug>(ale_detail) :ALEDetail
nnoremap <silent> <Plug>(ale_lint) :ALELint
nnoremap <silent> <Plug>(ale_reset_buffer) :ALEResetBuffer
nnoremap <silent> <Plug>(ale_disable_buffer) :ALEDisableBuffer
nnoremap <silent> <Plug>(ale_enable_buffer) :ALEEnableBuffer
nnoremap <silent> <Plug>(ale_toggle_buffer) :ALEToggleBuffer
nnoremap <silent> <Plug>(ale_reset) :ALEReset
nnoremap <silent> <Plug>(ale_disable) :ALEDisable
nnoremap <silent> <Plug>(ale_enable) :ALEEnable
nnoremap <silent> <Plug>(ale_toggle) :ALEToggle
nnoremap <silent> <Plug>(ale_last) :ALELast
nnoremap <silent> <Plug>(ale_first) :ALEFirst
nnoremap <silent> <Plug>(ale_next_wrap_warning) :ALENext -wrap -warning
nnoremap <silent> <Plug>(ale_next_warning) :ALENext -warning
nnoremap <silent> <Plug>(ale_next_wrap_error) :ALENext -wrap -error
nnoremap <silent> <Plug>(ale_next_error) :ALENext -error
nnoremap <silent> <Plug>(ale_next_wrap) :ALENextWrap
nnoremap <silent> <Plug>(ale_next) :ALENext
nnoremap <silent> <Plug>(ale_previous_wrap_warning) :ALEPrevious -wrap -warning
nnoremap <silent> <Plug>(ale_previous_warning) :ALEPrevious -warning
nnoremap <silent> <Plug>(ale_previous_wrap_error) :ALEPrevious -wrap -error
nnoremap <silent> <Plug>(ale_previous_error) :ALEPrevious -error
nnoremap <silent> <Plug>(ale_previous_wrap) :ALEPreviousWrap
nnoremap <silent> <Plug>(ale_previous) :ALEPrevious
nnoremap <silent> <Plug>(PrettierCliPath) :PrettierCliPath
nnoremap <silent> <Plug>(PrettierCliVersion) :PrettierCliVersion
nnoremap <silent> <Plug>(PrettierCli) :PrettierCli
nnoremap <silent> <Plug>(PrettierVersion) :PrettierVersion
nnoremap <silent> <Plug>(PrettierPartial) :PrettierPartial
nnoremap <silent> <Plug>(PrettierFragment) :PrettierFragment
nnoremap <silent> <Plug>(PrettierAsync) :PrettierAsync
nnoremap <silent> <Plug>(Prettier) :Prettier
imap S <Plug>ISurround
imap s <Plug>Isurround
imap  <Plug>Isurround
inoremap  u
imap <silent> m <Plug>(emmet-merge-lines)
imap <silent> A <Plug>(emmet-anchorize-summary)
imap <silent> a <Plug>(emmet-anchorize-url)
imap <silent> k <Plug>(emmet-remove-tag)
imap <silent> j <Plug>(emmet-split-join-tag)
imap <silent> / <Plug>(emmet-toggle-comment)
imap <silent> I <Plug>(emmet-image-encode)
imap <silent> i <Plug>(emmet-image-size)
imap <silent> N <Plug>(emmet-move-prev)
imap <silent> n <Plug>(emmet-move-next)
imap <silent> D <Plug>(emmet-balance-tag-outword)
imap <silent> d <Plug>(emmet-balance-tag-inward)
imap <silent> u <Plug>(emmet-update-tag)
imap <silent> ; <Plug>(emmet-expand-word)
imap <silent> , <Plug>(emmet-expand-abbr)
let &cpo=s:cpo_save
unlet s:cpo_save
set backspace=indent,eol,start
set balloonexpr=ale#balloon#Expr()
set cinoptions=:0,t0,(0,p0
set display=truncate
set fileencodings=ucs-bom,utf-8,default,latin1
set guifont=Nimbus\ Mono\ PS\ Regular
set helplang=en
set history=1000
set hlsearch
set ignorecase
set incsearch
set langnoremap
set nolangremap
set laststatus=2
set mouse=a
set nrformats=bin,hex
set printoptions=paper:letter
set ruler
set runtimepath=~/.vim,~/.vim/plugged/vim-fugitive,~/.vim/plugged/vim-airline,~/.vim/plugged/ale,~/.vim/plugged/gruvbox,~/.vim/plugged/vim-eunuch,~/.vim/plugged/vim-surround,~/.vim/plugged/vim-solarized8,~/.vim/plugged/jellybeans.vim,~/.vim/plugged/vim-ruby,~/.vim/plugged/vim-javascript,~/.vim/plugged/emmet-vim,~/.vim/plugged/vim-gitgutter,~/.vim/plugged/vim-rainbow,~/.vim/plugged/man.vim,~/.vim/plugged/vim-prettier,~/.vim/pack/plugins/start/vim-prettier,/var/lib/vim/addons,/etc/vim,/usr/share/vim/vimfiles,/usr/share/vim/vim82,/usr/share/vim/vim82/pack/dist/opt/justify,/usr/share/vim/vimfiles/after,/etc/vim/after,/var/lib/vim/addons/after,~/.vim/plugged/vim-javascript/after,~/.vim/after
set scrolloff=10
set showcmd
set showmatch
set smartcase
set suffixes=.bak,~,.swp,.o,.info,.aux,.log,.dvi,.bbl,.blg,.brf,.cb,.ind,.idx,.ilg,.inx,.out,.toc,.snap
set termencoding=utf-8
set textwidth=60
set ttimeout
set ttimeoutlen=100
set viminfo='1000,f1,<500
set wildmenu
set window=37
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd ~/repos/literate-octo-lamp/chess
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
argglobal
%argdel
$argadd chess.c
set stal=2
tabnew
tabnew
tabrewind
edit main.c
argglobal
balt make:\ \*\*\*\ \[Makefile
let s:cpo_save=&cpo
set cpo&vim
nmap <buffer> [c <Plug>(GitGutterPrevHunk)
nmap <buffer> \hp <Plug>(GitGutterPreviewHunk)
nmap <buffer> \hu <Plug>(GitGutterUndoHunk)
nmap <buffer> \hs <Plug>(GitGutterStageHunk)
xmap <buffer> \hs <Plug>(GitGutterStageHunk)
nmap <buffer> ]c <Plug>(GitGutterNextHunk)
xmap <buffer> ac <Plug>(GitGutterTextObjectOuterVisual)
omap <buffer> ac <Plug>(GitGutterTextObjectOuterPending)
xmap <buffer> ic <Plug>(GitGutterTextObjectInnerVisual)
omap <buffer> ic <Plug>(GitGutterTextObjectInnerPending)
let &cpo=s:cpo_save
unlet s:cpo_save
setlocal keymap=
setlocal noarabic
setlocal noautoindent
setlocal backupcopy=
setlocal balloonexpr=
setlocal nobinary
setlocal nobreakindent
setlocal breakindentopt=
setlocal bufhidden=
setlocal buflisted
setlocal buftype=
setlocal cindent
setlocal cinkeys=0{,0},0),0],:,0#,!^F,o,O,e
setlocal cinoptions=:0,t0,(0,p0
setlocal cinwords=if,else,while,do,for,switch
set colorcolumn=80
setlocal colorcolumn=80
setlocal comments=sO:*\ -,mO:*\ \ ,exO:*/,s1:/*,mb:*,ex:*/,://
setlocal commentstring=/*%s*/
setlocal complete=.,w,b,u,t,i
setlocal concealcursor=
setlocal conceallevel=0
setlocal completefunc=
setlocal nocopyindent
setlocal cryptmethod=
setlocal nocursorbind
set cursorcolumn
setlocal cursorcolumn
set cursorline
setlocal cursorline
setlocal cursorlineopt=both
setlocal define=^\\s*#\\s*define
setlocal dictionary=
setlocal nodiff
setlocal equalprg=
setlocal errorformat=
setlocal noexpandtab
if &filetype != 'c'
setlocal filetype=c
endif
setlocal fixendofline
setlocal foldcolumn=0
setlocal foldenable
setlocal foldexpr=0
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldmarker={{{,}}}
setlocal foldmethod=manual
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldtext=foldtext()
setlocal formatexpr=
setlocal formatoptions=croql
setlocal formatlistpat=^\\s*\\d\\+[\\]:.)}\\t\ ]\\s*
setlocal formatprg=
setlocal grepprg=
setlocal iminsert=0
setlocal imsearch=-1
setlocal include=^\\s*#\\s*include
setlocal includeexpr=
setlocal indentexpr=
setlocal indentkeys=0{,0},0),0],:,0#,!^F,o,O,e
setlocal noinfercase
setlocal iskeyword=@,48-57,_,192-255
setlocal keywordprg=
setlocal nolinebreak
setlocal nolisp
setlocal lispwords=
setlocal nolist
setlocal listchars=
setlocal makeencoding=
setlocal makeprg=
setlocal matchpairs=(:),{:},[:]
setlocal modeline
setlocal modifiable
setlocal nrformats=bin,hex
set number
setlocal number
setlocal numberwidth=4
setlocal omnifunc=ccomplete#Complete
setlocal path=
setlocal nopreserveindent
setlocal nopreviewwindow
setlocal quoteescape=\\
setlocal noreadonly
setlocal norelativenumber
setlocal norightleft
setlocal rightleftcmd=search
setlocal noscrollbind
setlocal scrolloff=-1
setlocal shiftwidth=8
setlocal noshortname
setlocal showbreak=
setlocal sidescrolloff=-1
setlocal signcolumn=auto
setlocal nosmartindent
setlocal softtabstop=0
setlocal nospell
setlocal spellcapcheck=[.?!]\\_[\\])'\"\	\ ]\\+
setlocal spellfile=
setlocal spelllang=en
setlocal spelloptions=
setlocal statusline=%!airline#statusline(1)
setlocal suffixesadd=
setlocal swapfile
setlocal synmaxcol=3000
if &syntax != 'c'
setlocal syntax=c
endif
setlocal tabstop=8
setlocal tagcase=
setlocal tagfunc=
setlocal tags=
setlocal termwinkey=
setlocal termwinscroll=10000
setlocal termwinsize=
setlocal textwidth=60
setlocal thesaurus=
setlocal thesaurusfunc=
setlocal noundofile
setlocal undolevels=-123456
setlocal varsofttabstop=
setlocal vartabstop=
setlocal virtualedit=
setlocal wincolor=
setlocal nowinfixheight
setlocal nowinfixwidth
set nowrap
setlocal nowrap
setlocal wrapmargin=0
silent! normal! zE
let &fdl = &fdl
let s:l = 59 - ((40 * winheight(0) + 22) / 45)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 59
normal! 0
tabnext
edit chess.h
argglobal
balt main.c
let s:cpo_save=&cpo
set cpo&vim
nmap <buffer> [c <Plug>(GitGutterPrevHunk)
nmap <buffer> \hp <Plug>(GitGutterPreviewHunk)
nmap <buffer> \hu <Plug>(GitGutterUndoHunk)
nmap <buffer> \hs <Plug>(GitGutterStageHunk)
xmap <buffer> \hs <Plug>(GitGutterStageHunk)
nmap <buffer> ]c <Plug>(GitGutterNextHunk)
xmap <buffer> ac <Plug>(GitGutterTextObjectOuterVisual)
omap <buffer> ac <Plug>(GitGutterTextObjectOuterPending)
xmap <buffer> ic <Plug>(GitGutterTextObjectInnerVisual)
omap <buffer> ic <Plug>(GitGutterTextObjectInnerPending)
let &cpo=s:cpo_save
unlet s:cpo_save
setlocal keymap=
setlocal noarabic
setlocal noautoindent
setlocal backupcopy=
setlocal balloonexpr=
setlocal nobinary
setlocal nobreakindent
setlocal breakindentopt=
setlocal bufhidden=
setlocal buflisted
setlocal buftype=
setlocal cindent
setlocal cinkeys=0{,0},0),0],:,0#,!^F,o,O,e
setlocal cinoptions=:0,t0,(0,p0
setlocal cinwords=if,else,while,do,for,switch
set colorcolumn=80
setlocal colorcolumn=80
setlocal comments=sO:*\ -,mO:*\ \ ,exO:*/,s1:/*,mb:*,ex:*/,://
setlocal commentstring=/*%s*/
setlocal complete=.,w,b,u,t,i
setlocal concealcursor=
setlocal conceallevel=0
setlocal completefunc=
setlocal nocopyindent
setlocal cryptmethod=
setlocal nocursorbind
set cursorcolumn
setlocal cursorcolumn
set cursorline
setlocal cursorline
setlocal cursorlineopt=both
setlocal define=^\\s*#\\s*define
setlocal dictionary=
setlocal nodiff
setlocal equalprg=
setlocal errorformat=
setlocal noexpandtab
if &filetype != 'cpp'
setlocal filetype=cpp
endif
setlocal fixendofline
setlocal foldcolumn=0
setlocal foldenable
setlocal foldexpr=0
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldmarker={{{,}}}
setlocal foldmethod=manual
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldtext=foldtext()
setlocal formatexpr=
setlocal formatoptions=croql
setlocal formatlistpat=^\\s*\\d\\+[\\]:.)}\\t\ ]\\s*
setlocal formatprg=
setlocal grepprg=
setlocal iminsert=0
setlocal imsearch=-1
setlocal include=^\\s*#\\s*include
setlocal includeexpr=
setlocal indentexpr=
setlocal indentkeys=0{,0},0),0],:,0#,!^F,o,O,e
setlocal noinfercase
setlocal iskeyword=@,48-57,_,192-255
setlocal keywordprg=
setlocal nolinebreak
setlocal nolisp
setlocal lispwords=
setlocal nolist
setlocal listchars=
setlocal makeencoding=
setlocal makeprg=
setlocal matchpairs=(:),{:},[:]
setlocal modeline
setlocal modifiable
setlocal nrformats=bin,hex
set number
setlocal number
setlocal numberwidth=4
setlocal omnifunc=ccomplete#Complete
setlocal path=
setlocal nopreserveindent
setlocal nopreviewwindow
setlocal quoteescape=\\
setlocal noreadonly
setlocal norelativenumber
setlocal norightleft
setlocal rightleftcmd=search
setlocal noscrollbind
setlocal scrolloff=-1
setlocal shiftwidth=8
setlocal noshortname
setlocal showbreak=
setlocal sidescrolloff=-1
setlocal signcolumn=auto
setlocal nosmartindent
setlocal softtabstop=0
setlocal nospell
setlocal spellcapcheck=[.?!]\\_[\\])'\"\	\ ]\\+
setlocal spellfile=
setlocal spelllang=en
setlocal spelloptions=
setlocal statusline=%!airline#statusline(1)
setlocal suffixesadd=
setlocal swapfile
setlocal synmaxcol=3000
if &syntax != 'cpp'
setlocal syntax=cpp
endif
setlocal tabstop=8
setlocal tagcase=
setlocal tagfunc=
setlocal tags=
setlocal termwinkey=
setlocal termwinscroll=10000
setlocal termwinsize=
setlocal textwidth=60
setlocal thesaurus=
setlocal thesaurusfunc=
setlocal noundofile
setlocal undolevels=-123456
setlocal varsofttabstop=
setlocal vartabstop=
setlocal virtualedit=
setlocal wincolor=
setlocal nowinfixheight
setlocal nowinfixwidth
set nowrap
setlocal nowrap
setlocal wrapmargin=0
silent! normal! zE
let &fdl = &fdl
let s:l = 36 - ((27 * winheight(0) + 22) / 45)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 36
normal! 0
tabnext
edit chess.c
argglobal
balt chess.h
let s:cpo_save=&cpo
set cpo&vim
nmap <buffer> [c <Plug>(GitGutterPrevHunk)
nmap <buffer> \hp <Plug>(GitGutterPreviewHunk)
nmap <buffer> \hu <Plug>(GitGutterUndoHunk)
nmap <buffer> \hs <Plug>(GitGutterStageHunk)
xmap <buffer> \hs <Plug>(GitGutterStageHunk)
nmap <buffer> ]c <Plug>(GitGutterNextHunk)
xmap <buffer> ac <Plug>(GitGutterTextObjectOuterVisual)
omap <buffer> ac <Plug>(GitGutterTextObjectOuterPending)
xmap <buffer> ic <Plug>(GitGutterTextObjectInnerVisual)
omap <buffer> ic <Plug>(GitGutterTextObjectInnerPending)
let &cpo=s:cpo_save
unlet s:cpo_save
setlocal keymap=
setlocal noarabic
setlocal noautoindent
setlocal backupcopy=
setlocal balloonexpr=
setlocal nobinary
setlocal nobreakindent
setlocal breakindentopt=
setlocal bufhidden=
setlocal buflisted
setlocal buftype=
setlocal cindent
setlocal cinkeys=0{,0},0),0],:,0#,!^F,o,O,e
setlocal cinoptions=:0,t0,(0,p0
setlocal cinwords=if,else,while,do,for,switch
set colorcolumn=80
setlocal colorcolumn=80
setlocal comments=sO:*\ -,mO:*\ \ ,exO:*/,s1:/*,mb:*,ex:*/,://
setlocal commentstring=/*%s*/
setlocal complete=.,w,b,u,t,i
setlocal concealcursor=
setlocal conceallevel=0
setlocal completefunc=
setlocal nocopyindent
setlocal cryptmethod=
setlocal nocursorbind
set cursorcolumn
setlocal cursorcolumn
set cursorline
setlocal cursorline
setlocal cursorlineopt=both
setlocal define=^\\s*#\\s*define
setlocal dictionary=
setlocal nodiff
setlocal equalprg=
setlocal errorformat=
setlocal noexpandtab
if &filetype != 'c'
setlocal filetype=c
endif
setlocal fixendofline
setlocal foldcolumn=4
setlocal foldenable
setlocal foldexpr=0
setlocal foldignore=#
setlocal foldlevel=4
setlocal foldmarker={{{,}}}
setlocal foldmethod=indent
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldtext=foldtext()
setlocal formatexpr=
setlocal formatoptions=croql
setlocal formatlistpat=^\\s*\\d\\+[\\]:.)}\\t\ ]\\s*
setlocal formatprg=
setlocal grepprg=
setlocal iminsert=0
setlocal imsearch=-1
setlocal include=^\\s*#\\s*include
setlocal includeexpr=
setlocal indentexpr=
setlocal indentkeys=0{,0},0),0],:,0#,!^F,o,O,e
setlocal noinfercase
setlocal iskeyword=@,48-57,_,192-255
setlocal keywordprg=
setlocal nolinebreak
setlocal nolisp
setlocal lispwords=
setlocal nolist
setlocal listchars=
setlocal makeencoding=
setlocal makeprg=
setlocal matchpairs=(:),{:},[:]
setlocal modeline
setlocal modifiable
setlocal nrformats=bin,hex
set number
setlocal number
setlocal numberwidth=4
setlocal omnifunc=ccomplete#Complete
setlocal path=
setlocal nopreserveindent
setlocal nopreviewwindow
setlocal quoteescape=\\
setlocal noreadonly
setlocal norelativenumber
setlocal norightleft
setlocal rightleftcmd=search
setlocal noscrollbind
setlocal scrolloff=-1
setlocal shiftwidth=8
setlocal noshortname
setlocal showbreak=
setlocal sidescrolloff=-1
setlocal signcolumn=auto
setlocal nosmartindent
setlocal softtabstop=0
setlocal nospell
setlocal spellcapcheck=[.?!]\\_[\\])'\"\	\ ]\\+
setlocal spellfile=
setlocal spelllang=en
setlocal spelloptions=
setlocal statusline=%!airline#statusline(1)
setlocal suffixesadd=
setlocal swapfile
setlocal synmaxcol=3000
if &syntax != 'c'
setlocal syntax=c
endif
setlocal tabstop=8
setlocal tagcase=
setlocal tagfunc=
setlocal tags=
setlocal termwinkey=
setlocal termwinscroll=10000
setlocal termwinsize=
setlocal textwidth=60
setlocal thesaurus=
setlocal thesaurusfunc=
setlocal noundofile
setlocal undolevels=-123456
setlocal varsofttabstop=
setlocal vartabstop=
setlocal virtualedit=
setlocal wincolor=
setlocal nowinfixheight
setlocal nowinfixwidth
set nowrap
setlocal nowrap
setlocal wrapmargin=0
187
normal! zo
267
normal! zo
274
normal! zo
328
normal! zo
336
normal! zo
336
normal! zc
328
normal! zc
391
normal! zo
482
normal! zo
483
normal! zo
500
normal! zo
507
normal! zo
532
normal! zo
556
normal! zo
580
normal! zo
604
normal! zo
608
normal! zo
629
normal! zo
676
normal! zo
679
normal! zo
939
normal! zo
940
normal! zo
let s:l = 942 - ((22 * winheight(0) + 22) / 45)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 942
normal! 0
tabnext 3
set stal=1
badd +1 main.c
badd +0 chess.c
badd +1 chess.h
badd +1 make:\ \*\*\*\ \[Makefile
badd +1 binary_search_tree.c
badd +1 binary_search_tree.h
badd +29 merge_sort.c
badd +120 ~/.vimrc
badd +2 merge_sort.h
badd +2 binary_search.c
badd +5 ~/repos/literate-octo-lamp/binary_search/main.c
badd +5 binary_search.h
badd +236 ~/repos/binary-search-trees/binary-search-tree.js
badd +54 array.c
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20 shortmess=filnxtToOS
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
