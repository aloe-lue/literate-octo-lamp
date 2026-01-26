function DateInsert()
        $delete
        read !date
endfunction

augroup cprograms
        autocmd BufReadPost *.c, *.h :set sw=4 sts=4
        autocmd BufReadPost *.cpp    :set sw=3 sts=3
augroup END

autocmd BufReadPost *.new execute "doautocmd BufReadPost " . expand("<afile>:r")

set eventignore=WinEnter,WinLeave
set eventignore=all
set eventignore=

