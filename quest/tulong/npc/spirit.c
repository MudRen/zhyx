#include <ansi.h>

inherit NPC;

void create()
{
        string *order = ({"��", "��", "��", "��", "��", "��", "ˮ", "��", "��", "��"});

        set_name((order[random(10)]) + "����", ({ "spirit" }) );
        set("long", "����һλ���Ծ�����С���飬������һ��͸��������\n");
        set("attitude", "friendly");

        set("max_qi", 10100);
        set("max_jing", 10101);
        set("max_jingli", 10100);
        set("max_neili", 10100);
        set("jiali", 400);
        set("neili", 20100);
        set("str", 25);
        set("con", 25);
        set("int", 25); 
        set("dex", 25);
        set("per", 30);

        set("combat_exp", 11100000);
        set_skill("blade", 800);
        set_skill("spirit-blade", 800);
        set_skill("spirit-dodge", 800);
        set_skill("parry", 800);
        set_skill("dodge", 800);

        map_skill("blade", "spirit-blade");
        map_skill("parry", "spirit-blade");
        map_skill("dodge", "spirit-dodge");
        setup();

        carry_object("/d/city/obj/gangdao")->wield();
}

int heal_up()
{
        if( environment() && !is_fighting() ) {
                call_out("leave", 1);
                return 1;
        }
        return ::heal_up() + 1;
}

void leave()
{
        message("vision",
                HIW + name() + "˵�����Ҳ��ܾ�������Ȼ�����Ѿ���������Ҫ�ؾ�����ˣ�\n\n"
                + name() + "����һ����͵Ĺ�â��������ʧ�����ˡ�\n" NOR, environment(),
                this_object() );
        destruct(this_object());
}

void invocation(object who)
{
        int i;
        object *enemy;

        message("vision",
                HIY "һ����紵����һ��С������������\n\n"
                + name() + "˵�������ǽ��ܾ��鵶���ٻ�����æ�ģ�\n" NOR,
                environment(), this_object() );
        enemy = who->query_enemy();
        i = sizeof(enemy);
        while(i--) {
                if( enemy[i] && living(enemy[i]) ) {
                        kill_ob(enemy[i]);
                        if( userp(enemy[i]) ) enemy[i]->fight_ob(this_object());
                        else enemy[i]->kill_ob(this_object());
                }
        }
        set_leader(who);
}

