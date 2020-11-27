// mishu.c 

inherit NPC;
inherit F_GUARDER;
#include <ansi.h> 

void create()
{
        set_name("����", ({ "fang fang", "fang" }));
        set("title", HIY "�����Ů����" NOR);
        set("long", "�����Ǻ����С�ء�\n");
        set("gender", "Ů��");
        set("age", 20);
        set("shen_type", 1);
        set("str", 18);
        set("int", 30);
        set("con", 25);
        set("dex", 20);
        set("per", 40);
        
        set("max_qi", 500);
        set("max_jing", 200);
        set("neili", 100);
        set("max_neili", 100);
        set("combat_exp", 2000);
        set("score", 200);

        set_skill("force", 20);
        set_skill("dodge", 20);
        set_skill("parry", 20);
        set_skill("unarmed", 20);

        set("chat_chance", 2);
        set("chat_msg", ({
              "��������һ���������ڵĿ��ȣ�����Ц���������˰ɣ��ȱ����Ȱɣ���\n",
              "��������ش��ź���ı�������Ҫ̫����ร����˯�ɡ���\n",
              "��������һֻ�����ȣ�����Ҫ�ϳԷ����棬��ֻ���Ȱɡ���\n",
        })); 

        set("inquiry", ([ 
          "����":"�����ҵġ�����������������",
          "haiyan":"�����ҵġ�����������������",
          "name":"�ҽз������Ǻ����С�أ��㿴�ҵ���ĺ���",
        ])); 

        setup();
        carry_object(__DIR__"bijini")->wear(); 
}


void relay_emote(object ob, string verb) 
{ 
     ob = this_player();
     switch(verb) 
     { 
         case "kiss": 
              command("shy"); 
              break; 
         case "love":
              command("protect1"); 
              break; 
         case "love1": 
              command("pei " + ob->query("id")); 
              break; 
         case "love2": 
              command("noway"); 
              break; 
         case "love3": 
              command("hammer " + ob->query("id")); 
              break; 
         case "fang": 
              command("kick2 " + ob->query("id")); 
              break; 
         case "chaxie": 
              ob->set_temp("desk_open",1);
              command("xixi " + ob->query("id")); 
              break; 
         default:
              command(verb + " " + ob->query("id")); 
              break; 
     }
}

void init() 
{ 
     object ob = this_player();
     ::init();
     if (wizardp(ob))
     {
        if ((string)ob->query("id") != "haiyan") 
        {
           message_vision("������$N˵��������ӭ$N����������͡���ʲô��Ҫ���ܷԸ�����\n",ob);
           return;
        }
        else
        {
           message_vision("������$N˵�������������������˰ɣ���ϴ���裬�Ҹ�����Ħ��Ħ����\n",ob);
           return;
        } 
     }
     else
     {
        message_vision("������ĿԲ������$N��ŭ�������������ĳ�˹֣����Ҵ������\n",ob);
//        ob->move("/d/city/wumiao");
        return;
     }
}

