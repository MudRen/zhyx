// huangboliu.c

#include <ansi.h>
inherit NPC;
inherit F_GUARDER;

int permit_pass(object me, string dir);

void create()
{
        set_name("�Ʋ���", ({ "huang boliu","huang","boliu"}) );
        set("gender", "����" );
        set("title", "������̷���������");
        set("nickname", HIW"������"NOR);
        set("age", 85);
        set("long", "һ�����룬ֱ�����أ���Ŀ���֮����\n");
        set("attitude", "peaceful");
        set("shen_type", -1);

        set("per", 21);
        set("str", 23);
        set("int", 23);
        set("con", 22);
        set("dex", 20);

        set("max_qi", 1000);
        set("max_jing",1000);
        set("neili", 1000);
        set("max_neili", 1000);
        set("combat_exp", 350000);
        set("jiali", 100);
        set("score", 30000);

        set_skill("force", 110); 
        set_skill("riyue-xinfa", 110); 
        set_skill("dodge", 110); 
        set_skill("piaomiao-shenfa", 110); 
        set_skill("hand", 110); 
        set_skill("huanmo-longtianwu", 110); 
        set_skill("cuff", 110); 
        set_skill("xuwu-piaomiao", 110);
        set_skill("parry", 110);
        set_skill("literate", 80);
        set_skill("sword", 110);
        set_skill("riyue-jian", 110);
        set_skill("blade", 110);
        set_skill("tianmo-dao", 110); 

        map_skill("force", "riyue-xinfa"); 
        map_skill("dodge", "piaomiao-shenfa"); 
        map_skill("hand", "huanmo-longtianwu"); 
        map_skill("cuff", "xuwu-piaomiao"); 
        map_skill("sword", "riyue-jian"); 
        map_skill("parry", "tianmo-dao"); 
        map_skill("blade", "tianmo-dao"); 

        prepare_skill("hand", "huanmo-longtianwu"); 
        prepare_skill("cuff", "xuwu-piaomiao"); 

        set("apply/dodge", 120);
        set_temp("apply/damage", 120);
        set_temp("apply/armor", 120);

        set("coagents", ({
        ([ "startroom" : "/d/heimuya/neishi",
           "id"        : "dongfang bubai" ]),
        }));

        create_family("�������",2,"���� ����������");

        setup();
        carry_object("/d/heimuya/npc/obj/dadao")->wield();
        carry_object("/clone/misc/cloth")->wear();
}

int permit_pass(object me, string dir) 
{ 
      object *inv; 
      int i; 

      if (! living(this_object()))  return 1;

      if (me->query("family/family_name") != "�������" &&
          dir == "westup")
      { 
          message_vision("$Nһ����ס$n����ǰ���Ǳ����صأ���λ" +
                         RANK_D->query_respect(me) +
                         "������ذɣ�������ûȤ��\n", this_object(), me);
          return notify_fail("�Ʋ������������ȥ��\n");
      } 

      notify_fail("����" + name() + "�����������ȥ��\n"); 

      inv = all_inventory(me); 
      for (i = 0; i < sizeof(inv); i++) 
      { 
          if (! userp(inv[i])) continue; 
          if ((string) inv[i]->query("family/family_name") != "�������")
          { 
                message_vision("$N��$n�ȵ����㱳����˭�����������£�\n",
                               this_object(), me);
                return 0;
          } 
      } 
      return 1; 
}

