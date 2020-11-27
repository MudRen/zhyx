#include <ansi.h>
inherit NPC;
void create()
{
        set_name(HIB"ˮӥ"NOR, ({ "hawk" }) );
        set("gender", "Ů��" );
         set("title",HIB"��Į��ӥ"NOR);
        set("age", 20);
        set("long","���ǻ�ӥ�����ã���С�Ͷ���Ϊ�飬�����ó�ѱ�ޣ���������\n");
        set("combat_exp", 5000000);
        set("attitude", "friendly");
        set("chat_chance", 15);
        set("chat_msg", ({
                (: random_move :)
        }) );
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
        add_action("do_train", "train");

}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(5) ) {
                case 0:
                        say( "ˮӥ˵������λ" + RANK_D->query_respect(ob)
                                + "���Ұ���ѱ�ޣ�����������к���ĵط���\n");
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
        if(!arg) return notify_fail("ˮӥ��������Ҫѱʲôѽ����\n");
        pet = present(arg,environment());
        if(!objectp(pet)) return notify_fail("ˮӥ��������Ҫѱʲôѽ����\n");
        if(pet->query("possessed") != me )
        return notify_fail("ˮӥ�������Ǻ�������İɣ���\n");
        //okey we identified the target, now the cost:
        cost = (int) pet->query("obedience");
        cost *= cost;
        if (me->query("balance") < cost*10000)
                return notify_fail("������û��"+chinese_number(cost)+"�����ӡ�\n");
        if((int)me->query("score") < cost/10)
        return notify_fail("��Ľ�����������"+chinese_number(cost/10)+"�㡣\n");
        pet->add("obedience",1);
        pet->save();
        me->add("balance",-cost*10000);
        me->add("score",-cost/10);
        command("say ���ˣ�\n");
        return 1;
}

