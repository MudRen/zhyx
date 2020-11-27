//���������񷢷���

#include <ansi.h>
inherit NPC;

#define NPC_FILE    __DIR__"npc"     //����NPC���ݿ��ļ�·��
#define PLACE_FILE  __DIR__"place"  //����ص����ݿ��ļ�·��

int ask_quest();
void whisper(object me, object ob);
void hunt(object me, object ob);
void patrol(object me, object ob);
string set_npc();
string set_place();
int job_ok();
int ask_cancel();
void reward(object me);
void item_reward(object me);

string *npc_list=({
"���ݳ�/����",
"���ݳ�/�⹭Ӱ",
"�����ӻ���/������",
"���ݵ���/���",
"����������ׯ/������",
"����Ǯׯ/Ǯ�ۿ�",
"���ݳ��µ�/����",
"̩ɽ��/���ҵ���",
"̩ɽ��/��ص���",
"̩ɽ��/���ɵ���",
"̩ɽ��/��������",
"�������ι���/��¡",
"�������ι���/֣��ˬ",
"�������ι���/������",
"��ػ���ľ��/�������",
"��ػ���ľ��/���촨",
"��ػ���ľ��/����",
"��ػ���ľ��/�����",
"��ػ���ľ��/�����",
"��ػ���ľ��/�ذ���",
"��ػ���ľ��/������",
"��ػ���ľ��/Ǯ�ϱ�",
"����/������",
"����/С����",
"�����ش���/Ҧ��",
"�����ӻ���/���ƹ�",
"��������/�ŵ¹�",
"����ȫ�۵¾�¥/���ϰ�",
"����ҩ��/ƽһָ",
"�����ӻ���/����ʵ",
"����С�ƹ�/�绨",
"����������/Ľ�ݺ�",
"�����ش���ҩ��/ʱ�Ź�",
"���������ھ�/����ɽ",
"����Ⱥ��¥/���ѩ",
"�������ǵ���/����ϲ",
"����ˮ����/������",
"�����鱦��/�𸴻�",
"������ջ/��ϲ»",
"�������ĸ�/���",
"����������/����",
"����������/����",
"����������/��ͨ��ʦ",
"������ˮ��/�ź�",
"������ˮ��/��Ⱥ",
"����/�����",
"��������/�̳���",
"�ɶ�������/�ƻ�",
"�ɶ��سǾ�¥/���ƹ�",
"�������/һ�ƴ�ʦ",
"����Ѧ�ǳ�����/Ѧ�ϰ�",
"��������·/��˼��",
"���ݸ���/������",
"���ݸ���/������",
"���ݱ��ͼ�/���ϼ�",
"���ݸ����ھ�/�׶�",
"���ݸ����ھ�/����",
"���ݸ����ھ�/ʷ��ͷ",
"���ݸ����ھ�/������",
"���ݸ����ھ�/֣��ͷ",
"���ݸ����ھ�/������",
"�������Ŵ��/����ͷ",
"�������д��/���˴�",
"���ݾ���/������",
"�����ᶽ����/��ʲ��",
"����ʯ��/ɳ�콭",
"��ɽӢ�ۻ��/��һ��",
"��ɽӢ��¥/������",
"��ɽӢ��¥/������",
"�����ĺ�Ǯׯ/��ѩԴ",
"�������޷�/������",
"����������/���ƹ�",
"�����ӻ���/������",
"�����������ε�/���ݷ�",
"����������/����",
"�������׵�/����",
"����������/����",
"��������/��",
"����Ǯׯ/����",
"������԰/��ܽ",
"�����ӻ���/�Ե���",
"���ݵ���/������",
"����ҩ���ʷ�/���ʱ�",
});

string *plc_list=({
"������/ϷԺ",
"������/С�ƹ�",
"������/���Ҵ���",
"������/����ǰԺ",
"������/��潹�",
"������/���ε�",
"������/Ⱥ��¥����",
"������/Ⱥ��¥����",
"������/Ⱥ��¥",
"������/������",
"������/����¥��¥",
"������/����¥",
"������/���ĸ�",
"������/�ʹ����",
"������/����",
"������/���Ӽ�",
"������/�����",
"������/ˮ����",
"������/����������",
"������/��ˮ��",
"������/�����ھִ�Ժ",
"������/������",
"������/������",
"������/�ĺ�Ǯׯ",
"������/�׻���",
"������/��̩�Ͽ�",
"������/��̩���",
"������/��̩����",
"������/С����",
"������/��������",
"������/Ⱥ��¥��¥",
"������/Ⱥ��¥��¥",
"������/�����",
"������/������",
"������/�ϰ�����",
"������/�ϰ����",
"������/���̸�",
"������/�����Ͽ�",
"������/���´��",
"������/���±���",
"������/�����",
"������/�����",
"������/��ڼ��",
"������/�������",
"������/�ش���ҩ��",
});

void create()
{
	set_name("����»", ({ "liang xinglu", "liang" }));
	set("title", "����֪��");
	set("gender", "����");
	set("age", 43);
	set("str", 20);
	set("dex", 20);
	set("long", "����������֪����\n");
	set("combat_exp", 50000);
	set("shen_type", 0);
	set("attitude", "heroism");
	set_skill("unarmed", 60);
	set_skill("force", 60);
	set_skill("sword", 60);
	set_skill("dodge", 60);
	set_skill("parry", 60);
	set_temp("apply/attack", 50);
	set_temp("apply/defense", 50);
	set_temp("apply/armor", 50);
	set_temp("apply/damage", 15);

	set("neili", 500); 
	set("max_neili", 500);
	set("jiali", 20);
       set("inquiry", ([                     
                       "����"      : (: ask_quest :),
                       "����"      : (: ask_quest :),
                       "quest"     : (: ask_quest :),
                       "���"      : (: job_ok :),
                       "����"      : (: job_ok :),
                       "ȡ��"      : (: ask_cancel :),
                       "ȡ������"  : (: ask_cancel :),
                       "cancel"   : (: ask_cancel :),
        ]));
	setup();
	carry_object("/d/changan/npc/obj/sword")->wield();
	carry_object("/d/changan/npc/obj/choupao")->wear();
}

//�������������ȡ����
int ask_quest()
{      
   object me, ob;
   int exp, i, all, have;
   string *ip;
   mapping record;    

   me = this_player();
   ob = this_object();
   have = 0;
   exp = me->query("combat_exp");

   if ( me->query("changanjob") )
   {
         message_vision(HIC "$N" HIC "��$n˵�������������Ѿ������ɷ��˲��£�"
                        "�겻�ɵĻ����ȸ���ȡ����\n"NOR, ob, me);
         return 1;
   }
   if ( me->query("combat_exp") > 800000 )
   {
         message_vision(HIC "$N" HIC "��$n˵������Ľ��������Ѿ��ܸ��ˣ�����"
                        "������Ҳ�첻���������ˡ�\n"NOR, ob, me);
         return 1;
   }
   
   if ( time() - me->query("changanjob_last_cancel") < 60 )
   {
         message_vision(CYN "$N" CYN "����$n���˿���˵���������ȡ����һ������"
                            "��һ���������ɡ���\n"NOR, ob, me);
                        return 1;
    } else 
    me->delete("changanjob_last_cancel");

    if ( time() - me->query("cajb_total_ask/time") > 3600 * 24 )
    {
                me->delete("cajb_total_ask");
                me->set("cajb_total_ask/time", time());
    }
    else
    {
      if ( me->query("cajb_total_ask/total") >= 1000 )             
      {
            message_vision(CYN "$N" CYN "����$n���˿���˵�������Բ���24Сʱ��"
                            "ֻ����ȡ1000�����񣡡�\n"NOR,
                            ob, me);
                        return 1;
       }
    }

   if (mapp(record = ob->query_temp("ip")))
   {
       record = ob->query_temp("ip");
       ip = keys(record);

       all = sizeof(ip);
       for (i = 0; i < all; i++)
       {
           if ( query_ip_number(me) == ip[i] )  have = 1;

           if ( query_ip_number(me) == ip[i] && 
                me->query("id") != record[ip[i]] ) 
           {
              if ( find_player(record[ip[i]])
                 && find_player(record[ip[i]])->query("changanjob"))
              {
                 write("������IP������" + record[ip[i]] +
                       "������������ \n");
                 have = 2;
              }
              if ( ! find_player(record[ip[i]]) || (find_player(record[ip[i]]) 
                   && ! find_player(record[ip[i]])->query("changanjob")))
              have = 0;
           }           
       }     
  
   } 
   else
       ob->set_temp("ip/" + query_ip_number(me), me->query("id") );

   if ( have == 2 ) return 1;
   if ( have == 0 )  
      ob->set_temp("ip/" + query_ip_number(me), me->query("id") );

   
   if ( sizeof(ip) > 20 ) ob->delete_temp("ip");

   me->add("cajb_total_ask/total", 1);

   message_vision(HIC "$N" HIC "��$n˵�����ţ���Ȼ������Ϊ���ų������ұ��"
                  "������¡�\n"NOR, ob, me);
   

   if ( exp >= 100000 )
   {
       switch(random(3))
        {    
         case 0 :
                 me->start_busy(2);                
                 call_other(__FILE__, "whisper", me, ob);
                 return 1;
         case 1 :             
                 me->start_busy(2);                
                 call_other(__FILE__, "patrol", me, ob);
                 return 1;                 
         case 2 :                              
                 me->start_busy(2);                  
                 call_other(__FILE__, "hunt", me, ob);  
                 return 1;                                
         default:
                 me->start_busy(2);               
                 call_other(__FILE__, "whisper", me, ob);
                 return 1;
        }
    } else
  //  if ( exp >= 50000 )
   {
       switch(random(2))
        {    
         case 0 :
                 me->start_busy(2);                
                 call_other(__FILE__, "whisper", me, ob);
                 return 1;
         case 1 :              
                 me->start_busy(2);                
                 call_other(__FILE__, "patrol", me, ob); 
                 return 1;                                                
         default:
                 me->start_busy(2);               
                 call_other(__FILE__, "whisper", me, ob);
                 return 1;
        }
    }  

    call_other(__FILE__, "patrol", me, ob);
    return 1;
}

void whisper(object me, object ob)
{
    string *wd, word;
    string npc, place, name, space;
    space = "                                                      ";
      
   wd = ({ "����","��Ծ","��ǿ","����","�Ͻ�","����","����","����","�ؼ�",
           "����","����","����","��ҵ","��ʦ","�ص�","����","�Ի�","����",
           "����","����","����","ֱǰ","����","����","����","����","�Ž�",
           "����","����","����","����","����","ͼǿ","����","��","����",
           "��ϸ","����","����","�Ż�","����","����","��ս","��ʤ","����",
           "�ش�","����","����","����","�Ի�","�׺�","ɣ��","�۾�","����",
           "�ڴ�","����","����","��˳","����","�ܷ�","ͼǿ","�Ṧ","ΰ��",
           "��ʤ","����","�","�ط�","����","��ͼ","����","Я��","����",
           "�͸�","����","�Ͷ�","����","����","����","��ѧ","��ʵ","����",
           "����","�²�","����","��ǿ","����","����","�","�ط�","����",
           "Э��","��ͳ","����","����","��ò","ǫ��","����","����","��ҵ",
           "����","����","����","ǿ��","�ڷ�","��ѧ","��֪","�̿�","����",
           "����","����","����","ͦ��","��ǿ","����","Ϊ��","����","����",
           "����","Т˳","���","����","�Ͽ�","��ʵ","���","����","����",
           "�ȱ�","׷��","����","��˽","Ϊ��","Ϊ��","����","����","����",
           "Ӣ��","ǫ��","ƴ��","�Ϲ�","����","Ż��","��Ѫ","����","��ҵ",
           "����","����","���","����","�ҳ�","̹��","����","�԰�","�ڼ�",
           "����","����","�½�","ǫ��","����","��η","�ʵ�","̽��","ʵ��",
           "��ʵ","��Ծ","����","����","����","ͼǿ","����","����","����",
           "��","����","��ǿ","����","ɱ��","����","Ϊ��","�Ҿ�","����",
           "����","��ƶ","����","��ȡ","��ʵ","�ܽ�","����","����","�Ƶ�", 
           "��־","��Т","����","����","����", });  

     word = wd[random(sizeof(wd))];

     npc = call_other(__FILE__, "set_npc");
     sscanf(npc, "%s/%s", place, name);

     if ( name == 0 || name == "" )
       {
            call_other(__FILE__,"whisper", me, ob);
            return;
       }  
     else
       {
            me->set("changanjob/kind", "whisper");                 
            me->set("changanjob/whisper", word);
            me->set("changanjob/place", place);
            me->set("changanjob/target", name);
            me->set("changanjob/time", time());

        //    if ( random(2) == 1 )
       //     word = word[0..1] + space[0..0] + word[2..3]; 
        /*  tell_object(me, WHT + ob->name() + "�����������˵������" +
                     "��ʵ"NOR HIG + place + WHT"��"HIG + name + NOR WHT"��"
                     "�����������ں������Եף�\n����Ұ�����µĽ�ͷ����ȥ��������"
                     "�����ǣ�\n\n" + TEXT2PIC_D->Display(word) + "\n\n"WHT + 
                     "��ȥ�ٻأ��������󣡡�\n"NOR); */ 
           word = space[0..random(20)] + word[0..1] + "\n\n" + 
                  space[0..random(20)] + word[2..3];

          tell_object(me, WHT + ob->name() + "�����������˵������" +
                     "��ʵ"NOR HIG + place + WHT"��"HIG + name + NOR WHT"��"
                     "�����������ں������Եף�\n����Ұ�����µĽ�ͷ����ȥ��������"
                     "�����ǣ�\n\n" + word + "\n\n"WHT + "��ȥ�ٻأ��������󣡡�\n"NOR);      
       }	
} 

string set_npc()
{
         string file, *lines, npc;
         npc = npc_list[random(sizeof(npc_list))];
         return npc;

 }

void patrol(object me, object ob)
{  
     string place, place1, place2;
     object gh;
     int i;

     message_vision(HIW "$N" HIW "˵�ű��ó�һ�ݹ�������$n��\n"NOR, ob, me);
     
     for( i=0; i < 5; i++ ) 
   	 {
    		 place = call_other(__FILE__, "set_place");
  		 sscanf(place, "%s/%s", place1, place2);

  		 if ( place2 == 0 || place2 == "" )
              {
                 call_other(__FILE__,"patrol", me, ob);
                 return;            
              }  
               else
              {
                 me->set("changanjob/place/"+ (i+1), place2);
              }
        }   

     me->set("changanjob/kind", "patrol");             
     me->set("changanjob/time", time());     
     gh = new(__DIR__"gonghan1");  
     for( i=0; i < 5; i++ )
        {
           gh->set("place/" + (i+1), me->query("changanjob/place/" + (i+1)));
        } 
     gh->set("owner", me->name());
     gh->move(me);
     me->set("changanjob/gonghan",gh);
}


void hunt(object me, object ob)
{  
     string place, place1, place2;
     object gh;

     place = call_other(__FILE__, "set_place");
     sscanf(place, "%s/%s", place1, place2);

     if ( place2 == 0 || place2 == "" )
       {
            call_other(__FILE__,"hunt", me, ob);
            return;
       }  
     else
       {    
            message_vision(HIW "$N" HIW "˵�ű��ó�һ�ݹ�������$n��\n"NOR, ob, me);
               gh = new(__DIR__"gonghan2");
               gh->set("owner", me->name());
               gh->set("place", place2);
               gh->move(me);

               me->set("changanjob/kind", "hunt");             
               me->set("changanjob/time", time());
               me->set("changanjob/place", place2);
               me->set("changanjob/gonghan",gh);

        }
}

string set_place()
{
         string file, *lines, where;
         where = plc_list[random(sizeof(plc_list))];
         return where;

}


int job_ok()
{
	object me, ob, dz;
       int exp, pot, tihui, score, weiwang;
       string msg;
       me = this_player();
       ob = this_object();
       msg = "";

       if ( ! me->query("changanjob") ) 
       {
          message_vision(HIR"$N"HIR"��$n�����󵨵��񣬱�����ʱ��������£�\n"
                          NOR, ob, me); 
          return 1;
       }

       if ( time() - me->query("changanjob/time") > 600 )
       {		
           message_vision(HIR "$N" HIR "��$n��ŭ��������ô��ô���������������Ч��̫���ˡ�\n" 
                           NOR, ob, me); 
          
          tell_object( me, CYN"\n��������������ϵ�̫�ã��޷�����ˣ���ȡ���ɡ�\n"NOR);
          return 1;
       }


       switch( me->query("changanjob/kind") )
        {    
        case "whisper" :
                me->start_busy(2);   
                if ( me->query("changanjob/whisper") )
                {
                   message_vision(HIR"$N"HIR"��$n��ŭ�����㶼��ûȥ�����������ʲô����\n" 
                                  NOR, ob, me);
                   return 1;                    
                }
                if ( me->query("changanjob/ok") )
                {   
                    call_other(__FILE__,"reward", me);                   
                }      
                else
                {	
                   message_vision(HIR"$N"HIR"��$n��ŭ�����ߣ����Ȼ������������������" 
                           "�������ﶼ����\n��������������ȥ���Եױ��Լ�����ɱ�ˣ�"
                           "�����̸��ܵģ�\n"NOR, ob, me);
                   tell_object(me, CYN"\n�ܲ��ң����������ʧ���ˣ���ȡ���ɡ�\n"NOR);
                }         
                return 1;
        case "patrol" :
                me->start_busy(2);   
                dz = me->query("changanjob/catch");
                if ( dz && objectp(present(dz->query("id"), environment(me))) )    
                {                    
                   message_vision(HIW"$N��$n��ϲ�����ţ��������ץ�������㹦����û��"
                                  "����Ҫ�����ʹ͡�\n�漴$N���һ�������ˣ����ٽ�׽���ĵ���Ѻ���ռࡣ\n"NOR
                                  HIY"\nֻ���������۽�" + dz->name() +  "Ѻȥ�˴��Ρ�\n\n"NOR, ob, me);
                   GIFT_D->bonus(me, ([ "prompt" : "ͨ�����׽��" + dz->name() +
                                                    HIG "�ľ���",
                                        "exp"    : random(100) + 200,
                                        "pot"    : random(100) + 100,
                                        "mar"    : random(30) + 30,
                                        "score"  : random(10) + 10, 
                                        "weiwang"  : random(10) + 10, ]), 1);                  
                   destruct(dz);
                   me->delete("changanjob/catch"); 
                } 
                message_vision(HIY"\n$N��$n���������й涨ҪѲ�ߵĵص㶼��ȥ���Ļ��ɽ�������������\n"
                               NOR, ob, me);
                return 1;
        case "hunt" :
                me->start_busy(2);                
                if ( ! me->query("changanjob/ok") )    
                {      
                   message_vision(HIR"$N"HIR"��$n��ŭ������ȥ��ɱ����������?"
                   "��Ҫ��ͼ��ƭ������\n"NOR, ob, me);
                   return 1;
                } else
                {
		     message_vision(HIY"\n$N��$n�������ѽ�ɱ������㽫�������������������������ʹ͡�\n"
                               NOR, ob, me);
                 }
               return 1;
        } 
}

int ask_cancel()
{
	object me, ob;
       int score, weiwang;
       string msg;
       me = this_player();
       ob = this_object();       

       if ( ! me->query("changanjob") ) 
       {
          message_vision(HIR"$N"HIR"��$n�����󵨵��񣬱�����ʱ��������£�\n"
                          NOR, ob, me); 
          return 1;
       }
        //���׽���������ٵ�
        if ( me->query("changanjob/catch") && 
             objectp(me->query("changanjob/catch"))  )
        destruct(me->query("changanjob/catch"));       
       // ��һ�ݹ������ڵĻ�Ҳ���ٵ�
        if ( me->query("changanjob/gonghan") && 
             objectp(me->query("changanjob/gonghan"))  )
        destruct(me->query("changanjob/gonghan"));    

         me->delete("changanjob");
         me->delete("changanjob_count");
         me->set("changanjob_last_cancel", time() );
         message_vision(HIY"$N"HIY"��$n�������С�¶��첻�ã����̫û���ˡ�\n"
                          NOR, ob, me); 
         tell_object(me, HIR"��ı��γ���������ȡ���ˣ�\n"NOR);
        if ( me->query("weiwang") > 10000 && me->query("score") > 10000 )
        {
           me->add("weiwang", -100);
           me->add("score", -100);

           tell_object(me, HIR"\n��������ͽ��������ܵ���һ����ʧ��\n"NOR);
        }
         return 1;
}

int accept_object(object me, object ob)
{    
     int i, flag; 
     object dz;    
     flag = 1;

     if ( ob != me->query("changanjob/gonghan") )
     {  command("say �󵨵����������������Ī������ϷŪ������"); 
        return 0; 
     }
     if ( ! me->query("changanjob") )
     {  command("say ������ʱ��������£�"); 
        return 0; 
     }     
     if ( time() - me->query("changanjob/time") > 600 )
     {		
          message_vision(HIR"$N""��$n��ŭ�������������ջ��ˣ���������ô��������������������ʹ͡�\n" 
                           NOR, this_object(), me);           
          me->delete("changanjob");          
          destruct(ob);
          return 1;
      }
      dz = me->query("changanjob/catch");

      if ( dz && ! objectp(present(dz->query("id"), environment(me))) ) 
      {
          message_vision(HIW"$N��$n�����㲻��ץ���˵�������ô������������\n"NOR,ob, me);
          return 0;
      }   

      if ( dz && objectp(present(dz->query("id"), environment(me))) )    
         {                    
             message_vision(HIW"$N��$n��ϲ�����ţ��������ץ�������㹦����û��"
                            "����Ҫ�����ʹ͡�\n�漴$N���һ�������ˣ����ٽ�׽���ĵ���Ѻ���ռࡣ\n"NOR
                            HIY"\nֻ���������۽�" + dz->name() +  "Ѻȥ�˴��Ρ�\n\n"NOR, ob, me);
                   GIFT_D->bonus(me, ([ "prompt" : "ͨ�����׽��" + dz->name() +
                                                    HIG "�ľ���",
                                        "exp"    : random(100) + 300,
                                        "pot"    : random(100) + 200,
                                        "mar"    : random(30) + 30,
                                        "score"  : random(10) + 10, 
                                        "weiwang"  : random(10) + 10, ]), 1);                  
                   destruct(dz);
                   me->delete("changanjob/catch"); 
          } 

     if ( me->query("changanjob/kind") == "patrol" )
     { 
        for( i=0; i < 5; i++ )
           {
             if ( ! ob->query("placeok/" + (i+1)) ) flag = 0;
           } 
        if ( flag == 0 )
           {
              message_vision(HIR"$N""��$n��ŭ���������ϵļ�¼��ʾ�����еص�δȥѲ�����"
                             "�����˵�����\n" NOR, this_object(), me); 
              return 0;
           }
     } 
    
    /*if ( me->query("changanjob/kind") == "patrol" && me->query("changanjob/lost") )    
    {      
        message_vision(HIR"$N"HIR"��$n��ŭ����������СС��������ץ��ס��"
                       "���к���Ŀ���򱾸�������\n"NOR, this_object(), me);
        return 0;
    }*/
    if ( me->query("changanjob/kind") == "hunt" && ! me->query("changanjob/ok") )    
    {      
        message_vision(HIR"$N"HIR"��$n��ŭ������ȥ��ɱ����������?"
                       "��Ҫ��ͼ��ƭ������\n"NOR, this_object(), me);
        return 0;
    }

    call_other(__FILE__,"reward", me);
    destruct(ob);
    return 1;

} 

void reward(object me)
{                
        string msg;   
        object ob, pay; 
        int exp, pot, tihui, score,  weiwang;

        ob = this_object();

        exp = random(100) + 400;
        pot = random(100) + 300;                           
        score = random(20) + 30;
        weiwang = random(20) + 30; 

        if ( me->query("changanjob/kind") == "whisper" )
        {            
           if ( me->query("combat_exp") > 100000 )
           {
              exp = exp / 2;
              pot = pot / 2;
           }    
        } else
          tihui = 50 + random(50); 

        if ( me->query("changanjob/kind") == "patrol" )
        {
           exp = exp * 3;
           pot = pot * 3;
        }
        me->delete("changanjob");
        me->add("changanjob_count",1);   //�ۼ������������һ��
        if ( me->query("changanjob_count") > 1000 )
        { me->set("changanjob_count",1); }     //�ۼƳ���1000���1

        if ( me->query("potential") >= me->query_potential_limit() )
        {  pot = 1; }
        if ( me->query("experience") >= me->query_experience_limit() && tihui > 0)
        {  tihui = 1; }       

        tell_object(me, HIC + ob->name() + "��������ţ����������ɵò���" 
                       "�������±�����ʹ͡�\n"NOR + HIW"�����˼���������\n"NOR); 
        message("vision", HIC + ob->name() + "��" + me->name() +
                 "�����ţ����������ɵò����������±�����ʹ͡�\n" NOR HIW 
                 + me->name() + "����˼���������\n"NOR, environment(me), ({me})); 

        me->add("combat_exp", exp );
        me->add("potential", pot );
        me->add("experience", tihui);

        if ( me->query("gongxian") < 2000 )
            me->add("gongxian", 4+random(3));

        me->add("score", score);
        me->add("weiwang", weiwang);  
        pay = new("/clone/money/silver");
        pay->set_amount(1 + random(2));
        pay->move(me, 1);         
        
        msg = HIG"\nͨ����ζ�����\n������"NOR HIR + chinese_number(exp) + 
                   HIG"�㾭�飬"NOR HIW + chinese_number(pot) + NOR HIG"��Ǳ�ܣ�";
        if (tihui > 0) 
             msg += "�Լ�"HIY + chinese_number(tihui) + HIG"��ʵս��ᡣ"NOR;            
             msg += HIW"\n���ɹ��ס����������Լ�����Ҳ�����˲�ͬ�̶ȵ���ߡ�\n" NOR;
        tell_object( me, msg); 

       if ( me->query("changanjob_count") % 100 == 0 ||
            me->query("changanjob_count") % 50 == 0  )  //ÿ���һ�ٸ��������item����
       
           call_other(__FILE__,"item_reward", me); 
       
}

void item_reward(object me)
{                
        // ���һ�ٸ�����
        string *ob4_list = ({
                "/clone/fam/pill/puti4",
                "/clone/fam/pill/sheli4",
                "/clone/fam/gift/str1",
                "/clone/fam/gift/int1",
                "/clone/fam/gift/con1",
                "/clone/fam/gift/dex1",
                "/clone/fam/item/handan",
                "/clone/fam/item/bixue",
                "/clone/fam/item/zijin",
                "/clone/fam/item/wujin",
                "/clone/fam/item/taijin",
                "/clone/fam/pill/renshen1",
                "/clone/fam/pill/lingzhi1",
                "/clone/fam/pill/xuelian1",
        });
        // ������ٸ�����
        string *ob5_list = ({
                "/clone/fam/etc/lv5a",
                "/clone/fam/etc/lv5b",
                "/clone/fam/etc/lv5c",
                "/clone/fam/etc/lv5d",
                "/clone/fam/etc/lv5e",
                "/clone/fam/pill/renshen2",
                "/clone/fam/pill/lingzhi2",
                "/clone/fam/pill/xuelian2",
        });
        // ������ٸ�����
        string *ob6_list = ({
                "/clone/fam/gift/str2",
                "/clone/fam/gift/int2",
                "/clone/fam/gift/con2",
                "/clone/fam/gift/dex2",
                "/clone/fam/pill/renshen3",
                "/clone/fam/pill/lingzhi3",
                "/clone/fam/pill/xuelian3",
                "/clone/fam/item/zhenlong",
                "/clone/fam/item/jiulei",
                "/clone/fam/item/panlong",
        });
        // ����İٸ�����
        string *ob7_list = ({
                "/clone/tattoo/buttock1",
                "/clone/tattoo/buttock2",
                "/clone/tattoo/buttock3",
                "/clone/tattoo/buttock4",
                "/clone/tattoo/buttock5",
                "/clone/tattoo/buttock6",
                "/clone/tattoo/buttock7",
                "/clone/tattoo/buttock8",
        });
        // �����ٸ�����
        string *ob8_list = ({
                "/clone/fam/gift/str2",
                "/clone/fam/gift/int2",
                "/clone/fam/gift/con2",
                "/clone/fam/gift/dex2",
                "/clone/fam/pill/renshen3",
                "/clone/fam/pill/lingzhi3",
                "/clone/fam/pill/xuelian3",
                "/clone/fam/etc/lv7a",
                "/clone/fam/etc/lv7b",
                "/clone/fam/etc/lv7c",
                "/clone/fam/etc/lv7d",
        });
        // ������ٸ�����
        string *ob9_list = ({
                "/clone/tattoo/body1",
                "/clone/tattoo/body2",
                "/clone/tattoo/body3",
                "/clone/tattoo/body4",
                "/clone/tattoo/body5",
                "/clone/tattoo/body6",
                "/clone/tattoo/body7",
                "/clone/tattoo/body8",
                "/clone/tattoo/body9",
                "/clone/tattoo/body10",
        });
        // ����߰ٸ�����
        string *ob10_list = ({
                "/clone/fam/pill/yulu",
                "/clone/fam/pill/dimai",
                "/clone/fam/pill/renshen4",
                "/clone/fam/pill/lingzhi4",
                "/clone/fam/pill/xuelian4",
                "/clone/fam/item/baxian",
                "/clone/fam/item/kunlun",
                "/clone/fam/item/haoyue",
                "/clone/fam/item/leihuo",
                "/clone/fam/item/yinzhu",
        });
        // ��ɰ˰ٸ�����
        string *ob11_list = ({
                "/clone/tattoo/spcs1",
                "/clone/tattoo/spcs2",
                "/clone/tattoo/spcs3",
                "/clone/tattoo/spcs4",
                "/clone/tattoo/spcs5",
                "/clone/tattoo/spcs6",
                "/clone/tattoo/spcs7",
                "/clone/tattoo/spcs8",
                "/clone/tattoo/spcs9",
                "/clone/tattoo/spcs10",
        });
        // ��ɾŰٸ�����
        string *ob12_list = ({
                "/clone/fam/skpaper/blade1",
                "/clone/fam/skpaper/claw1",
                "/clone/fam/skpaper/club1",
                "/clone/fam/skpaper/cuff1",
                "/clone/fam/skpaper/dagger1",
                "/clone/fam/skpaper/finger1",
                "/clone/fam/skpaper/hammer1",
                "/clone/fam/skpaper/hand1",
                "/clone/fam/skpaper/parry1",
                "/clone/fam/skpaper/staff1",
                "/clone/fam/skpaper/strike1",
                "/clone/fam/skpaper/sword1",
                "/clone/fam/skpaper/throwing1",
                "/clone/fam/skpaper/unarmed1",
                "/clone/fam/skpaper/whip1",                
        });
        // ���һǧ������
        string *ob13_list = ({
                "/clone/fam/gift/str3",
                "/clone/fam/gift/int3",
                "/clone/fam/gift/con3",
                "/clone/fam/gift/dex3",
                "/clone/fam/item/yanluo",
                "/clone/fam/item/lihuo",
                "/u/sanben/obj/fig", 
        });
        string un, gift;
        object ob;
        gift = "clone/fam/pill/zhengqi"; //50��������������

        if (me->query("changanjob_count") == 1000)
        {
                gift = ob13_list[random(sizeof(ob13_list))];                
        } else
        if (me->query("changanjob_count") == 900)
        {
                gift = ob12_list[random(sizeof(ob12_list))];                
        } else
        if (me->query("changanjob_count") == 800)
        {
                gift = ob11_list[random(sizeof(ob11_list))];                
        } else
        if (me->query("changanjob_count") == 700)
        {
                gift = ob10_list[random(sizeof(ob10_list))];                
        } else
        if (me->query("changanjob_count") == 600)
        {
                gift = ob9_list[random(sizeof(ob9_list))];                
        } else
        if (me->query("changanjob_count") == 500)
        {
                gift = ob8_list[random(sizeof(ob8_list))];                
        } else
        if (me->query("changanjob_count") == 400)
        {
                gift = ob7_list[random(sizeof(ob7_list))];                
        } else
        if (me->query("changanjob_count") == 300)
        {
                gift = ob6_list[random(sizeof(ob6_list))];                
        } else
        if (me->query("changanjob_count") == 200)
        {
                gift = ob5_list[random(sizeof(ob5_list))];                
        } else
        if (me->query("changanjob_count") == 100)
        {
                gift = ob4_list[random(sizeof(ob4_list))];                
        }  
      
          

        ob = new(gift);
        ob->move(me);

        if (ob->query("base_unit"))
                un = ob->query("base_unit");
        else
                un = ob->query("unit");
   
        message("vision", HIC + this_object()->name() + "��" + me->name() +
                 "�����˴α��������ʹ���һ" + un + NOR + ob->name() +NOR
                 HIC"�����ʹ�����\n\n"NOR, environment(me), ({me})); 

        tell_object(me, HIC + this_object()->name() + "��������˴α��������ʹ���һ" 
                    + un + NOR + ob->name() +NOR HIC"�����ʹ�����\n\n"NOR  
                    HIG"������һ" + un + NOR + ob->name() + NOR HIG"��\n"NOR);
      
}


