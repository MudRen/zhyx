//created by mudbug on 2003/3/5 

#include <ansi.h>
inherit "/inherit/npcsave";
string convert_en(string strs);
int totle_user(string sr);

int tell_users();


string *family = ({
   "������","shaolin",
   "�䵱��","wudang",
   "ؤ��","gaibang",
   "ȫ���","quanzhen",
   "��ɽ��","huashan",
   "���ϻ���","duan",
   "Ľ������","murong",
   "ѩɽ��","xueshan",
   "���չ�","lingjiu",
   "������","emei",
   "�һ���","taohua",
   "������","shenlong",
   "��Ĺ��","gumu",
   "������","xingxiu",
   "��ң��","xiaoyao",
   "Ѫ����","xuedao",
   "��ɽ����","jianzong",
   "ŷ������","ouyang",
   "�������","hu",
   "�컨��","honghuahui",
});


void create()
{
        set_name( HIW "�л�Ӣ��" NOR, ({ "china hero" }) );
       set("title", HIR"���ɵ���Ա"NOR);
        set("age", 30);
        set("max_qi", 5000);
        set("max_qi", 5000);
        set("max_jing", 5000);
        set("max_neili", 5000);
        set("neili", 5000);

        set("str", 100);
        set("con", 100);
        set("int", 100);
        set("dex", 100);
        set("kar", 100);
        set("per", 100);
        set("combat_exp", 10000000);

        set_skill("stick", 500);
        set_skill("unarmed", 500);
        set_skill("parry", 500);
        set_skill("dodge", 500);
        set_temp("apply/attack", 100);
        set_temp("apply/defense", 100);
        set_temp("apply/armor", 100);
        set_temp("apply/damage", 100);
        setup();

}

void init()
{
         ::init();
         if(!query_temp("working")){
         this_object()->set_temp("working",1);
         remove_call_out("work");
         call_out("work",1);
          }
}

void work()
{
      object *player;
      object env;
      int i,m,j,k,num,dummynum;
      int exp,average;

     remove_call_out("work");

     this_object()->delete("menpai");      
     this_object()->delete("mudbug");      

     this_object()->save();

     player = users();
     m=sizeof(player);
     j=sizeof(family);
     dummynum=0;

     for(i=0;i<m;i++){
     if(wizardp(player[i])||player[i]->query("combat_exp")+player[i]->query("score")<300000) {
                 dummynum++;
                 continue;}
          for(k=0;k<j;k++){
              if(!mapp(player[i]->query("family"))||player[i]->query("family/family_name")!=family[k])             
                continue;
              exp=(player[i]->query("combat_exp")+player[i]->query("daoxing"))/1000;
              this_object()->add("menpai/"+family[k+1],exp);
              this_object()->add("menpai/totle",exp);
              this_object()->add("mudbug/"+family[k+1],1);
                           }
                    }
  if(!this_object()->query("menpai/totle")) return;
  average=this_object()->query("menpai/totle")/(m-dummynum);
  this_object()->delete("menpai/totle");

  message("sys",HIR"�����ɵ��顿"+HIC"�л�Ӣ��(china hero):�������ݾ�ֵΪ"+chinese_number(average)+"\n"NOR,users());
   for(i=1;i<j;i+=2){
     this_object()->set("menpai/"+family[i],!this_object()->query("menpai/"+family[i])||
                                               this_object()->query("menpai/"+family[i])*100/average>115
                                                 ||this_object()->query("menpai/"+family[i])*100/average<85
                                                   ?115:this_object()->query("menpai/"+family[i])*100/average);
                     }

      this_object()->save();
      tell_users();  

}

int tell_users()
{

        int i,j,k,m,n,aimnum,addnum,success,usernum,samenum;
        string *str,msg,name,log;
        mapping menpai;

       menpai=this_object()->query("menpai");
       if (!sizeof(menpai)) return 1; 
       str= keys(menpai);
      log="";
      aimnum=(int)sizeof(menpai);
      msg =  "\n            �� "+BCYN HIW+"�л�Ӣ����������ͳ�ư�"NOR" ��\n";
      msg += "���������ө��ߩ������������ө����������ߩө���������\n";
        msg += "�� ���� ��   ��      ��   ��  �� ��     ���Ա�ϵ����\n";
        msg += "�ĩ������ة����������������ة������������ة���������\n";
        for(k=0;k<(int)sizeof(menpai);k++){
         for(i=0;i<(int)sizeof(menpai);i++){
          addnum=0;
           for(m=0;m<(int)sizeof(menpai);m++){
              if((int)this_object()->query("menpai/"+str[m])<=(int)this_object()->query("menpai/"+str[i]))
                 addnum++; }     
                  if(addnum>=aimnum&&strsrch(log,str[i])<0) {
                   aimnum--;
                    log+=str[i];
                     for(n=0,success=0;n<1000;n++){
                       for(j=1;j<sizeof(family);j+=2){
                         if(family[j]!=str[i]) continue;
                          name=family[j-1];
                           usernum=this_object()->query("mudbug/"+str[i]);
                            samenum=totle_user(name);
 msg += sprintf("��  %-5s %-18s %3d/%-8d %4d    ��\n"NOR,chinese_number((int)sizeof(menpai)-aimnum),name,usernum,samenum,
        (int)this_object()->query("menpai/"+str[i]));
                       success=1;}
                     if(success) break;
                          }
         if(!aimnum&&this_object()->query("menpai/"+str[i])>=114)
                this_object()->delete("menpai"); //here to no add damage because of all menpai is same 115 or one 114
                    }
                 if(!aimnum) break; 
                 }
                if(!aimnum) break; 
           }

        msg += "����������������������������������������������������\n";
        msg += BLINK HIG"    �л�Ӣ�� "NOR + NATURE_D->game_time() + "ͳ�ơ�\n";
        message("channel:chat",msg,users());
      remove_call_out("work");
      call_out("work",3600);
        return 1;

}

string convert_en(string strs)
{

     int i;
     string chin;

     for(i=0;i<sizeof(family);i+=2){
           if(family[i]==strs) chin=family[i+1];
               }
        return chin;

}

int totle_user(string sr)
{

     int i,samenum;
     object *player;
     player=users();

 for(i=0,samenum=0;i<sizeof(player);i++){
    if(!wizardp(player[i])&&player[i]->query("family/family_name")&&player[i]->query("family/family_name")==sr)
      samenum++;}
    return samenum;

}
