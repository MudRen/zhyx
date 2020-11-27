//zsh_guard.c 

inherit NPC; 

#include <ansi.h> 

int ask_zsh(object me, object ob); 
void create() 
{ 
     set_name("����",({"shou wei","guard"}) ); 
     set("long","����һλ����Ӣ�˲����������ˡ�\n"); 
     set("title","���������"); 
     set("gender","����"); 
     set("age",20); 
     set("combat_exp",100); 
     set("inquiry",([ 
          "������" : (: ask_zsh :), 
     ]) ); 
     setup(); 
     carry_object("/clone/cloth/cloth")->wear();  
     carry_object("/clone/weapon/changjian")->wield();  
} 

int ask_zsh(object me, object ob) 
{ 
     me=this_player(); 
     ob=this_object(); 
     if (me->query("bang_good/name")!="������" && (int)me->query("shen") >= 0 ) 
     { 
           tell_object(me,"�����������¿��˿��㣬����һ����\n"); 
           tell_object(me,"��������˵����������������᣿���ҵ������棬���Լ���ȥ�ɡ���\n"); 
           me->set_temp("good_zsh",1); 
           return 1; 
     } 
     if( me->query("bang_bad") || (int)me->query("shen") < 0 ) 
     { 
           command("say �ߣ����������������������������ǲ�������ģ�"); 
           return 1; 
     } 

     tell_object(me,"������ֵ�������Ҷ��ǻ����ֵܣ���γ����԰�����\n"); 
     return 1; 
} 

