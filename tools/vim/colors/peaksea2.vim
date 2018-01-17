
" 256color dark terminal support here
hi Normal		ctermfg=252	ctermbg=235	cterm=NONE
" Comment/Uncomment the following line to disable/enable transparency
"hi Normal		ctermfg=252	ctermbg=NONE	cterm=NONE
hi Comment		ctermfg=186	ctermbg=NONE	cterm=NONE
hi Constant		ctermfg=110	ctermbg=NONE	cterm=NONE
hi Number		ctermfg=179	ctermbg=NONE	cterm=NONE
hi Identifier	ctermfg=219	ctermbg=NONE	cterm=NONE
hi Statement	ctermfg=153	ctermbg=NONE	cterm=NONE
hi PreProc		ctermfg=84	ctermbg=NONE	cterm=NONE
hi Type		ctermfg=153	ctermbg=NONE	cterm=NONE
hi Special		ctermfg=179	ctermbg=NONE	cterm=NONE
hi Error		ctermfg=209	ctermbg=NONE	cterm=NONE
hi Todo		ctermfg=88	ctermbg=186	cterm=NONE
hi Search		ctermfg=White	ctermbg=LightBlue	cterm=NONE
hi Visual		ctermfg=16	ctermbg=153	cterm=NONE
hi Cursor		ctermfg=16	ctermbg=46	cterm=NONE

" hi CursorIM	ctermfg=16	ctermbg=201	cterm=NONE
hi StatusLine	ctermfg=16	ctermbg=153	cterm=NONE
"hi LineNr		ctermfg=249	ctermbg=NONE	cterm=NONE
hi LineNr ctermfg=102 ctermbg=237 cterm=NONE
hi Question		ctermfg=16	ctermbg=186	cterm=NONE
hi ModeMsg		ctermfg=fg	ctermbg=33	cterm=NONE
hi VisualNOS	ctermfg=fg	ctermbg=18	cterm=NONE
hi SpecialKey	ctermfg=153	ctermbg=NONE	cterm=NONE
hi NonText		ctermfg=69	ctermbg=233	cterm=NONE
" Comment/Uncomment the following line to disable/enable transparency
"hi NonText		ctermfg=69	ctermbg=NONE	cterm=NONE
hi Directory	ctermfg=110	ctermbg=NONE	cterm=NONE


hi ErrorMsg		ctermfg=186	ctermbg=88	cterm=NONE
hi MoreMsg		ctermfg=150	ctermbg=NONE	cterm=NONE
hi Title		ctermfg=77	ctermbg=NONE	cterm=NONE


hi WarningMsg	ctermfg=209	ctermbg=NONE	cterm=NONE
hi WildMenu		ctermfg=16	ctermbg=186	cterm=NONE
hi Folded		ctermfg=NONE	ctermbg=DarkGrey cterm=NONE
hi FoldColumn	ctermfg=DarkGrey ctermbg=NONE cterm=NONE
hi DiffAdd		ctermfg=NONE	ctermbg=18	cterm=NONE
hi DiffChange	ctermfg=NONE	ctermbg=90	cterm=NONE
hi DiffDelete	ctermfg=69	ctermbg=234	cterm=NONE
hi DiffText		ctermfg=16	ctermbg=150	cterm=NONE
hi SignColumn	ctermfg=254	ctermbg=28	cterm=NONE
hi IncSearch	ctermfg=White	ctermbg=LightBlue	cterm=NONE
hi StatusLineNC	ctermfg=16	ctermbg=250	cterm=NONE
hi VertSplit	ctermfg=239	ctermbg=239	cterm=NONE
hi Underlined	ctermfg=111	ctermbg=NONE	cterm=underline 
hi Ignore		ctermfg=16	ctermbg=NONE


if v:version >= 700
  if has('spell')
	" the ctermsp= is not supported in Vim 7 we simply ignored
	if 0
	  hi SpellBad	cterm=undercurl	ctermbg=NONE	ctermfg=209
	  hi SpellCap	cterm=undercurl	ctermbg=NONE	ctermfg=69
	  hi SpellRare	cterm=undercurl	ctermbg=NONE	ctermfg=219
	  hi SpellLocal	cterm=undercurl	ctermbg=NONE	ctermfg=153
	else
	  hi SpellBad	cterm=undercurl	ctermbg=NONE	ctermfg=NONE
	  hi SpellCap	cterm=undercurl	ctermbg=NONE	ctermfg=NONE
	  hi SpellRare	cterm=undercurl	ctermbg=NONE	ctermfg=NONE
	  hi SpellLocal	cterm=undercurl	ctermbg=NONE	ctermfg=NONE
	endif
  endif

  hi Pmenu		ctermfg=White	ctermbg=DarkGrey
  hi PmenuSel	ctermfg=Black	ctermbg=White	cterm=NONE

  hi TabLine	ctermfg=fg	ctermbg=Black	cterm=NONE
  hi TabLineFill	ctermfg=fg	ctermbg=Black	cterm=NONE
  hi TabLineSel	ctermfg=fg	ctermbg=DarkBlue	cterm=NONE

  hi CursorColumn	ctermfg=NONE	ctermbg=88	cterm=NONE
  hi CursorLine	ctermfg=NONE	ctermbg=NONE	cterm=underline
  hi MatchParen	ctermfg=NONE	ctermbg=33
  hi TabLine	cterm=underline  
  hi TabLineFill	cterm=underline  
  hi Underlined	cterm=underline  
  hi CursorLine	cterm=underline 
endif
