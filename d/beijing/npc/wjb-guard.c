
inherit NPC; 

#include <ansi.h> 

int ask_wjb(object me, object ob); 
void create() 
{ 
     set_name("����",({"shou wei","guard"}) ); 
     set("long","����һλ���޼����������\n"); 
     set("title","�޼������"); 
     set("gender","����"); 
     set("age",20); 
     set("combat_exp",100000); 
     set_skill("dodge",150); 
     set_skill("force",150); 
     set_skill("literate",150); 
     set_skill("unarmed",150); 
     set("inquiry",([ 
          "�޼���" : (: ask_wjb :), 
     ]) ); 
     setup(); 
} 

int ask_wjb(object me, object ob) 
{ 
     me=this_player(); 
     ob=this_object(); 
     if (me->query("bang_good/name")!="�޼���" && (int)me->query("shen") >= 0 ) 
     { 
           command("famours " + me->query("id")); 
           tell_object(me,"����Ц���еض���˵����������������޼���ɣ�����������\n"); 
           me->set_temp("good_wjb2",1); 
           return 1; 
     } 
     if( me->query("bang_bad") || (int)me->query("shen") < 0 ) 
     { 
           ob->command("say ��������аħ������Ҵ�ô��\n"); 
           return 1; 
     } 

     tell_object(me,"������ֵ�����ͬΪ�����ֵܣ���γ����԰�����\n"); 
     return 1; 
} 

