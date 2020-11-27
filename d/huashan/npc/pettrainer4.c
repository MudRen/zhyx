// #pragma save_binary


// Tie@fy
#include <ansi.h>
inherit NPC;
void create()
{
        set_name("����", ({ "wanghu" }) );
        set("gender", "����" );
        set("age", 22);
        set("long","һ�����θߴ�ĺ���\n");
        set("combat_exp", 5000);
        set("attitude", "friendly");
        set("chat_chance", 15);
        set("title",HIW"ѵ��ʦ"NOR);
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
                                + "���������ҶԴ�train�����㸶���ӣ�\n");
                        break;
                case 1:
                        say( "����Ц������λ" + RANK_D->query_respect(ob)
                                + "�����ģ��˲������ģ�\n");

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
	if(!arg) return notify_fail("������������Ҫʲôѽ����\n");
	pet = present(arg,environment());
	if(!objectp(pet)) return notify_fail("������������Ҫʲôѽ����\n");
	if(pet->query("possessed") != me )
	return notify_fail("�����������Ǻ�������İɣ���\n");
//okey we identified the target, now the cost:
	cost = to_int(sqrt(to_float((int)pet->query("combat_exp"))))/5;
	if (cost > 200) cost = 200;
	gold = present("gold_money", me);
        if(!gold) return notify_fail("������û�н��ӡ�\n");
        if((int) gold->query_amount() < cost)
        return notify_fail("������û��"+chinese_number(cost)+"�����ӡ�\n");
	if((int)me->query("score") < cost)
	return notify_fail("������۲���"+chinese_number(cost)+"�㡣\n");
	pet->add("combat_exp",cost*50);
	pet->save();
	gold->add_amount(-cost);
	me->add("score",-cost);
	command("say ���ˣ��´��ٴ�\n");
	return 1;
}
