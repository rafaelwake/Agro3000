
 #define SAIDA_1 12          //bomba de gotejamento ligada no pino 12
 #define SAIDA_2 11          //bomba de aspersao ligada no pino 11
 #define BOTAO 2             //0=aspersao  1 = gotejamento
 #define Sensor A0           //saida do sensor de solo
 #define BT Serial.begin(9600);


     int val;                //variavel que armazena os dados enviado pelo sensor

     int limite = 50;          //variavel do limite de operação do sensor
     int tempo=0,bomba=0,tempoatual=0,tempoinicial=0,intervalo=0; 
     int botao=0;
     char rx;
         
 void setup()
 {
  
      pinMode(SAIDA_1, OUTPUT);    //define pino 12 como saida
      pinMode(SAIDA_2, OUTPUT);    //define pino 11 como saida
      pinMode(BOTAO, INPUT);       //define botão como entrada
//      SoftwareSerial Serial1(10, 11); // RX, TX
      Serial.begin(9600);
      Serial.println("inicio");
    while (!Serial) {
    /*** Aguardando o estabelecimento da conexão ***/
  }
    
}
 
 void loop() 
   {
     
    if(Serial.available() > 0)            //comunicaçao com o bluetooth
     {

       rx = Serial.read();
       
          if(rx=='D') {
           digitalWrite(SAIDA_1,LOW);
           digitalWrite(SAIDA_2,LOW);
          while(Serial.read()!= 'E');
         }
           if(rx=='G') botao=1;               //comando enviados pelo aplicativo  
           if(rx=='A') botao=0; 

      }
   
      Serial.print("modo= ");

     if(botao==0)                       //acionado liga o sistema de aspersor
        {
       Serial.println("aspersao");         
        }
     else if(botao==1)                  //acionado liga o sistema de gotejamento
        {
       Serial.println("gotejamento");
        }
      
      val = analogRead(Sensor);         //faz leitura da umidade do solo 
      val = map(val, 0, 1023, 0, 100);
   
    //  Serial.println(val);
     // BT.println(val);
      
     if(val <= 30)
       {
       Serial.println(" Solo Seco ");
       Serial.print(" Humidade em: ");
       Serial.print(val);
        Serial.println("%");
       }
     else if(val <= 60)
       {  
       Serial.println(" Solo umido ");
       Serial.print(" Humidade em: ");
       Serial.print(val);
       Serial.println("%");
      }
      else if(val <= 90)
        {  
       Serial.println(" Super umido ");
       Serial.print(" Humidade em: ");
       Serial.print(val);
       Serial.println("%");
       }
      else if(val > 90)
      {  
       Serial.println(" Submerco ");
       Serial.print(" Humidade em: ");
       Serial.print(val);
       Serial.println("%");
      }
      
       if(val>limite)
          { 
       digitalWrite(SAIDA_1,LOW);
       digitalWrite(SAIDA_2,LOW); 
          }
       if(val<=limite)
        
       digitalWrite(SAIDA_1,HIGH);
       digitalWrite(SAIDA_2,LOW);
         
       if(botao==1)
             {
        digitalWrite(SAIDA_1,LOW);   
        digitalWrite(SAIDA_2,HIGH);
             }     
           
        if(val > 50)       
      {
       
        digitalWrite(SAIDA_1,LOW);
        digitalWrite(SAIDA_2,LOW);        
        Serial.println("desligando a bomba ...");
      } 
     
     {
         delay(1000);
   }
 }
