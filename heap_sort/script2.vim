vim9script

try
        read ~/templates/pascal.tmpl
catch /E484:/
        echo "Sorry, the Pascal template file cannot be found."
endtry
