// zhang2.c

#include <ansi.h>
#include "riyue.h"

inherit NPC;
inherit F_MASTER;

mixed ask_pfm();

void create()
{
    set_name("�ų���", ({"zhang chengyun", "zhang", "chengyun"}));
    set("nickname", HIW "��Գ��ħ" NOR );
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
    set_skill("hand", 150);
    set_skill("huanmo-longtianwu", 150);
    set_skill("cuff", 180);
    set_skill("xuwu-piaomiao", 180);
    set_skill("fengyun-bianhuan", 180);
    set_skill("parry", 150);
    set_skill("literate", 110);
    set_skill("sword",150);
    set_skill("riyue-jian",150);

    map_skill("force", "riyue-xinfa");
    map_skill("dodge", "piaomiao-shenfa");
    map_skill("hand", "huanmo-longtianwu");
    map_skill("cuff", "fengyun-bianhuan");
    map_skill("sword", "riyue-jian");
    map_skill("parry", "fengyun-bianhuan");

    create_family("�������", 2, "����");

    set("inquiry", ([
        "������ӿ"  : (: ask_pfm :),
        "����"      : (: ask_pfm :),
    ]));

    setup();
    carry_object("/clone/misc/cloth")->wear();
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
    ob->set("title", HIM "�������" HIW "��Գ����" NOR);
}

mixed ask_pfm()
{
      object me = this_player();

      if (me->query("can_perform/fengyun-bianhuan/fengyun"))
              return "���ǲ���������д�һ�£�";

      if (me->query("family/family_name") != query("family/family_name"))
              return "������书�������֣���λ" + RANK_D->query_respect(me) +
                     "��Ȼ��ѧ���������������Σ�";

      if (me->query_skill("fengyun-bianhuan", 1) < 150)
              return "��ķ��Ʊ�û��������ң�������ô�����أ�";

      message_vision(HIW "$n" HIW "��$N" HIW "���˵�ͷ��ע�⿴����ˡ�\n" HIW
                     "ֻ��$n" HIW "˫ȭһ����ʱһ��������$N" HIW
                     "������$N" HIW "�о��ؿ�������ѹ����������������\n" NOR,
                     me, this_object());
      command("say ����û�У�");
      tell_object(me, HIC "��ѧ���ˡ�������ӿ����һ�С�\n" NOR);
      if (me->can_improve_skill("cuff"))
            me->improve_skill("cuff", 160000);
      me->set("can_perform/fengyun-bianhuan/fengyun", 1);
      return 1;
}

