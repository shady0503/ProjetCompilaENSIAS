//------------------------------------------------------------------------------
// AfficherToke: affiche le token reconnu, sa valeur et sa classe lexicale
// cette fonction n'est pas necesaire. Elle est là, juste pour tester 
//l'ablyseur lexicale
//------------------------------------------------------------------------------
void AfficherToken(TSym_Cour SYM){
	switch(SYM.cls){
	   case	PROGRAM_TOKEN:   printf("%s          %s\n",SYM.nom,"PROGRAM_TOKEN "); break;
	   case VAR_TOKEN:       printf("%s          %s\n",SYM.nom,"VAR_TOKEN ");     break;
	   case CONST_TOKEN:     printf("%s          %s\n",SYM.nom,"CONST_TOKEN ");   break;
	   case PV_TOKEN:        printf("%s          %s\n"," ;     ","PV_TOKEN ");    break;
	   case ID_TOKEN:        printf("%s          %s\n",SYM.nom,"ID_TOKEN");       break;
	   case PRG_TOKEN:       printf("%s          %s\n"," (     ","PRG_TOKEN ");   break;
	   case PRD_TOKEN:       printf("%s          %s\n","  )    ","PRD_TOKEN");    break;
	   case END_TOKEN:       printf("%s          %s\n",SYM.nom,"END_TOKEN");      break;
	   case EGAL_TOKEN:      printf("%s          %s\n","  =    ","EGAL_TOKEN");   break;
	   case BEGIN_TOKEN:     printf("%s          %s\n",SYM.nom,"BEGIN_TOKEN");    break;
	   case VIRG_TOKEN:      printf("%s          %s\n","  ,    ","VIRG_TOKEN");   break;
	   case AFFECT_TOKEN:    printf("%s          %s\n","  :=   ","AFFECT_TOKEN"); break;
	   case THEN_TOKEN:      printf("%s          %s\n",SYM.nom,"THEN_TOKEN");     break;
	   case IF_TOKEN:        printf("%s          %s\n",SYM.nom,"IF_TOKEN");       break;
	   case WHILE_TOKEN:     printf("%s          %s\n",SYM.nom,"WHILE_TOKEN ");   break;
	   case WRITE_TOKEN:     printf("%s          %s\n",SYM.nom,"WRITE_TOKEN ");   break;
	   case READ_TOKEN:      printf("%s          %s\n",SYM.nom,"READ_TOKEN ");    break;
	   case DO_TOKEN:        printf("%s          %s\n",SYM.nom,"DO_TOKEN");       break;
	   case NUM_TOKEN:       printf("%s          %s\n",SYM.nom,"NUM_TOKEN");      break;
	   case PT_TOKEN:        printf("%s          %s\n","  .    ","PT_TOKEN");     break;
	   case PLUS_TOKEN:      printf("%s          %s\n","  +    ","PLUS_TOKEN");   break;
	   case DIFF_TOKEN:      printf("%s          %s\n","  <>   ","DIFF_TOKEN");   break;
	   case SUP_TOKEN:       printf("%s          %s\n","  >    ","SUP_TOKEN");    break;
	   case INF_TOKEN:       printf("%s          %s\n","  <    ","INF_TOKEN");    break;
	   case INFEG_TOKEN:     printf("%s          %s\n","  <=   ","INFEG_TOKEN");  break;
	   case SUPEG_TOKEN:     printf("%s          %s\n","  >=   ","SUPEG_TOKEN");  break;
	   case MOINS_TOKEN:     printf("%s          %s\n","  -    ","MOINS_TOKEN");  break;
	   case MULTI_TOKEN:     printf("%s          %s\n","  *    ","MULTI_TOKEN");  break;
	   case DIV_TOKEN:       printf("%s          %s\n","  /    ","DIV_TOKEN");    break;
	   case DIEZE_TOKEN:     printf("%s          %s\n","  EOF  ","DIEZE_TOKEN");  break;
	   default:              printf("%s","ERR_TOKEN");                            break;
	}
	getch();
}

