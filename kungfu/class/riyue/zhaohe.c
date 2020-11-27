// zhaohe.c

#include <ansi.h>
#include "riyue.h"

inherit NPC;
inherit F_MASTER;

mixed ask_pfm();

void create()
{
    set_name("�Ժ�", ({"zhao he", "zhao", "he"}));
    set("nickname", HIC "������ħ" NOR );
    set("title", "������̳���");
    set("gender", "����");
    set("age", 42);
    set("shen_type", -1);
    set("long", "����������̳��ϡ�\n");
    set("attitude", "peaceful");

    set("per", 21);
    set("str", 30);
    set("int", 30);
    set("con", 30);
    set("dex", 30);

    set("qi", 3000);
    set("max_qi", 3000);
    set("jing", 1000);
    set("max_jing", 1000);
    set("neili", 3000);
    set("max_neili", 3000);
    set("jiali", 300);

    set("combat_exp", 1500000);
    set("score", 0);

    set_skill("force", 150);
    set_skill("riyue-xinfa", 150);
    set_skill("dodge", 150);
    set_skill("piaomiao-shenfa", 150);
    set_skill("hand", 180);
    set_skill("huanmo-longtianwu", 150);
    set_skill("tianmo-shou", 180);
    set_skill("cuff", 150);
    set_skill("xuwu-piaomiao", 150);
    set_skill("parry", 150);
    set_skill("literate", 110);
    set_skill("sword",150);
    set_skill("riyue-jian",150);

    map_skill("force", "riyue-xinfa");
    map_skill("dodge", "piaomiao-shenfa");
    map_skill("hand", "tianmo-shou");
    map_skill("cuff", "xuwu-piaomiao");
    map_skill("sword", "riyue-jian");
    map_skill("parry", "tianmo-shou");

    create_family("�������", 2, "����");

    set("inquiry", ([
        "�߻�"  : (: ask_pfm :),
        "����"  : (: ask_pfm :),
    ]));

    setup();
    carry_object("/d/heimuya/npc/obj/leizhendang");
    carry_object("/clone/misc/cloth")->wear();
    carry_object("/d/heimuya/npc/obj/yancao");
}

void attempt_apprentice(object ob)
{
    if(! permit_recruit(ob))  return;

    if((int)ob->query_skill("riyue-xinfa", 1) < 120)
    {
         command("say ���̵��ڹ��ķ��㻹û���ã���Ҫ���¿๦���У�");
         return;
    }

    command("recruit " + ob->query("id"));
    ob->set("title", HIM "�������" HIC "���커��" NOR);
}

mixed ask_pfm()
{
      object me = this_player();

      if (me->query("can_perform/tianmo-shou/cui"))
              return "���ǲ���������д�һ�£�";

      if (me->query("family/family_name") != query("family/family_name"))
              return "������书�������֣���λ" + RANK_D->query_respect(me) +
                     "��Ȼ��ѧ���������������Σ�";

      if (me->query_skill("tianmo-shou", 1) < 150)
              return "�����ħ�ֻ��������ң�������ô�����أ�";

      message_vision(HIC "$n" HIC "��$N" HIC "���˵�ͷ��ע�⿴���ˡ�\n" HIC
                     "ֻ��$n" HIC "���һ�����ҿ�һ����˲�������$N" HIC
                     "����ǰ�����������ĳ�һ�ơ�\n" HIC
                     "$N" HIC "һ�㣬��ʱ��Ȼ��ͨ��\n" NOR,
                     me, this_object());
      command("say ����û�У�");
      tell_object(me, HIR "��ѧ���ˡ��߻꡹��һ�С�\n" NOR);
      if (me->can_improve_skill("hand"))
            me->improve_skill("hand", 160000);
      me->set("can_perform/tianmo-shou/cui", 1);
      return 1;
}

