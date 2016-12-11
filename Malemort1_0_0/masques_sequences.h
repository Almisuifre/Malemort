/* --- ZONE D'ARRET DES TRAINS / CANTONS -- */
boolean tZoneArret[NB_ZA];  //Tableau des état des zones d'arrets

//Séquence pour des trains manquant
//{ZA0,ZA1,ZA2,ZA3,ZA4,ZA5,ZA6}
boolean tMaskDefalutEmpty[NB_ZA] = {0,0,0,0,0,0,0};  //Toutes les zones d'arrets sont vides

//Séquence pour 1 train et 7 cantons
//{ZA0,ZA1,ZA2,ZA3,ZA4,ZA5,ZA6}
boolean tMaskTrain1Seq0[NB_ZA] = {1,0,0,0,0,0,0};  //ZA0 -> ZA1
boolean tMaskTrain1Seq1[NB_ZA] = {0,1,0,0,0,0,0};  //ZA1 -> ZA2 / ZA3
boolean tMaskTrain1Seq2[NB_ZA] = {0,0,1,0,0,0,0};  //ZA2 -> ZA4
boolean tMaskTrain1Seq3[NB_ZA] = {0,0,0,1,0,0,0};  //ZA3 -> ZA4
boolean tMaskTrain1Seq4[NB_ZA] = {0,0,0,0,1,0,0};  //ZA4 -> ZA5 / ZA6
boolean tMaskTrain1Seq5[NB_ZA] = {0,0,0,0,0,1,0};  //ZA5 -> ZA0
boolean tMaskTrain1Seq6[NB_ZA] = {0,0,0,0,0,0,1};  //ZA6 -> ZA0

//Séquence pour 2 trains et 7 cantons
boolean tMaskTrain2Seq0[NB_ZA] = {1,0,0,0,1,0,0};  //ZA0 -> ZA1
boolean tMaskTrain2Seq1[NB_ZA] = {0,1,0,0,1,0,0};  //ZA1 -> ZA2 / ZA3
boolean tMaskTrain2Seq2[NB_ZA] = {0,0,1,0,1,0,0};  //ZA4 -> ZA5 / ZA6
boolean tMaskTrain2Seq3[NB_ZA] = {0,0,0,1,1,0,0};  //ZA4 -> ZA5 / ZA6
boolean tMaskTrain2Seq4[NB_ZA] = {0,0,1,0,0,1,0};  //ZA5 -> ZA0
boolean tMaskTrain2Seq5[NB_ZA] = {0,0,1,0,0,0,1};  //ZA6 -> ZA0
boolean tMaskTrain2Seq6[NB_ZA] = {0,0,0,1,0,1,0};  //ZA5 -> ZA0
boolean tMaskTrain2Seq7[NB_ZA] = {0,0,0,1,0,0,1};  //ZA6 -> ZA0
boolean tMaskTrain2Seq8[NB_ZA] = {1,0,1,0,0,0,0};  //ZA2 -> ZA4
boolean tMaskTrain2Seq9[NB_ZA] = {1,0,0,1,0,0,0};  //ZA3 -> ZA4

//Séquence pour 3 trains et 7 cantons
boolean tMaskTrain3Seq0[NB_ZA] = {1,0,0,0,1,1,0};  //ZA0 -> ZA1
boolean tMaskTrain3Seq1[NB_ZA] = {1,0,0,0,1,0,1};  //ZA0 -> ZA1
boolean tMaskTrain3Seq2[NB_ZA] = {0,1,0,0,1,1,0};  //ZA1 -> ZA2 / ZA3
boolean tMaskTrain3Seq3[NB_ZA] = {0,1,0,0,1,0,1};  //ZA1 -> ZA2 / ZA3
boolean tMaskTrain3Seq4[NB_ZA] = {0,0,1,0,1,1,0};  //ZA5 -> ZA0
boolean tMaskTrain3Seq5[NB_ZA] = {0,0,1,0,1,0,1};  //ZA6 -> ZA0
boolean tMaskTrain3Seq6[NB_ZA] = {0,0,0,1,1,1,0};  //ZA5 -> ZA0
boolean tMaskTrain3Seq7[NB_ZA] = {0,0,0,1,1,0,1};  //ZA6 -> ZA0
boolean tMaskTrain3Seq8[NB_ZA] = {1,0,1,0,1,0,0};  //ZA4 -> ZA5 / ZA6
boolean tMaskTrain3Seq9[NB_ZA] = {1,0,0,1,1,0,0};  //ZA4 -> ZA5 / ZA6
boolean tMaskTrain3Seq10[NB_ZA] = {1,0,1,0,0,1,0};  //ZA2 -> ZA4
boolean tMaskTrain3Seq11[NB_ZA] = {1,0,0,1,0,1,0};  //ZA3 -> ZA4
boolean tMaskTrain3Seq12[NB_ZA] = {1,0,1,0,0,0,1};  //ZA2 -> ZA4
boolean tMaskTrain3Seq13[NB_ZA] = {1,0,0,1,0,0,1};  //ZA3 -> ZA4

//Séquence pour 4 trains et 7 cantons
boolean tMaskTrain4Seq0[NB_ZA] = {1,0,1,0,1,1,0};  //ZA0 -> ZA1
boolean tMaskTrain4Seq1[NB_ZA] = {1,0,0,1,1,1,0};  //ZA0 -> ZA1
boolean tMaskTrain4Seq2[NB_ZA] = {1,0,1,0,1,0,1};  //ZA0 -> ZA1
boolean tMaskTrain4Seq3[NB_ZA] = {1,0,0,1,1,0,1};  //ZA0 -> ZA1
boolean tMaskTrain4Seq4[NB_ZA] = {0,1,0,1,1,1,0};  //ZA5 -> ZA0
boolean tMaskTrain4Seq5[NB_ZA] = {0,1,1,0,1,1,0};  //ZA5 -> ZA0
boolean tMaskTrain4Seq6[NB_ZA] = {0,1,0,1,1,0,1};  //ZA6 -> ZA0
boolean tMaskTrain4Seq7[NB_ZA] = {0,1,1,0,1,0,1};  //ZA6 -> ZA0
boolean tMaskTrain4Seq8[NB_ZA] = {1,1,1,0,1,0,0};  //ZA4 -> ZA5 / ZA6
boolean tMaskTrain4Seq9[NB_ZA] = {1,1,0,1,1,0,0};  //ZA4 -> ZA5 / ZA6
boolean tMaskTrain4Seq10[NB_ZA] = {1,1,1,0,0,1,0};  //ZA2 -> ZA4
boolean tMaskTrain4Seq11[NB_ZA] = {1,1,1,0,0,0,1};  //ZA2 -> ZA4
boolean tMaskTrain4Seq12[NB_ZA] = {1,1,0,1,0,1,0};  //ZA3 -> ZA4
boolean tMaskTrain4Seq13[NB_ZA] = {1,1,0,1,0,0,1};  //ZA3 -> ZA4
boolean tMaskTrain4Seq14[NB_ZA] = {1,1,0,0,1,1,0};  //ZA1 -> ZA2 / ZA3
boolean tMaskTrain4Seq15[NB_ZA] = {1,1,0,0,1,0,1};  //ZA1 -> ZA2 / ZA3

//Séquence pour 5 trains et 7 cantons
boolean tMaskTrain5Seq0[NB_ZA] = {1,0,1,1,1,1,0};  //ZA0 -> ZA1
boolean tMaskTrain5Seq1[NB_ZA] = {1,0,1,1,1,0,1};  //ZA0 -> ZA1

boolean tMaskTrain5Seq2[NB_ZA] = {0,1,1,1,1,1,0};  //ZA5 -> ZA0
boolean tMaskTrain5Seq3[NB_ZA] = {0,1,1,1,1,0,1};  //ZA6 -> ZA0

boolean tMaskTrain5Seq4[NB_ZA] = {1,1,1,1,1,0,0};  //ZA4 -> ZA5 / ZA6
boolean tMaskTrain5Seq5[NB_ZA] = {1,1,1,1,1,1,0};  //ZA4 -> ZA5 / ZA6
boolean tMaskTrain5Seq6[NB_ZA] = {1,1,1,1,1,0,1};  //ZA4 -> ZA5 / ZA6

boolean tMaskTrain5Seq7[NB_ZA] = {1,1,1,1,0,1,0};  //ZA2 / ZA3 -> ZA4
boolean tMaskTrain5Seq8[NB_ZA] = {1,1,1,1,0,0,1};  //ZA2 / ZA3 -> ZA4

boolean tMaskTrain5Seq9[NB_ZA] = {1,1,0,1,1,0,1};  //ZA1 -> ZA2 / ZA3
boolean tMaskTrain5Seq10[NB_ZA] = {1,1,0,1,1,1,0};  //ZA1 -> ZA2 / ZA3

boolean tMaskTrain5Seq11[NB_ZA] = {1,1,1,0,1,0,1};  //ZA1 -> ZA2 / ZA3
boolean tMaskTrain5Seq12[NB_ZA] = {1,1,1,0,1,1,0};  //ZA1 -> ZA2 / ZA3



