#pragma save_binary


// Smallfish@Jdmr
#include <ansi.h>
inherit NPC;
void create()
{
        set_name("����", ({ "dai ban" }) );
        set("gender", "Ů��" );
        set("age", 62);
set("long","������һ���ܶ��ص�Ů�������Թ�Ƨ��ר���붯��Ϊ�飬�ó�ѱ�ޣ�xunlian����\n");
        set("combat_exp", 50000000);
	set("title",HIW"���ﰮ����"NOR);
        set("attitude", "friendly");
        set("chat_chance", 15);
        set("per",29);
        setup();
        carry_object("/clone/cloth/cloth")->wear();

}

void init()
{	
        object ob;
        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_train", "xunlian");

}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(5) ) {
                case 0:
                        say( "����˵������λ" + RANK_D->query_respect(ob)
                                + "����ũ����ȥ��ô��\n");
                        break;
                case 1:
                        say( "����̾������λ" + RANK_D->query_respect(ob)
                                + "���Ұ���ѱ�ޣ������һ��ȥ��ũ�ܵĵ�ͼ�ɡ�\n");
                        break;
        }
}

int do_train(string arg)
{
	object me,pet,gold;
	int cost;
        me = this_player();
        if(me->is_busy())
        return notify_fail("����һ��������û����ɡ�\n");
	if(!arg) return notify_fail("�����������Ҫѱʲôѽ����\n");
	pet = present(arg,environment());
	if(!objectp(pet)) return notify_fail("�����������Ҫѱʲôѽ����\n");
	if(pet->query("possessed") != me )
	return notify_fail("����������Ǻ�������İɣ���\n");
//okey we identified the target, now the cost:
	cost = (int) pet->query("obedience");
	cost *= cost;
        cost /= 20;
	if (cost < 1) cost = 1;
	gold = present("gold_money", me);
        if(!gold) return notify_fail("������û�н��ӡ�\n");
        if((int) gold->query_amount() < cost)
        return notify_fail("������û��"+chinese_number(cost)+"�����ӡ�\n");
	if((int)me->query("score") < cost/10)
	return notify_fail("������۲���"+chinese_number(cost/10)+"�㡣\n");
	pet->add("obedience",1);
	pet->save();
	gold->add_amount(-cost);
	me->add("score",-cost/10);
	command("say ���ˣ�\n");
	return 1;
}
