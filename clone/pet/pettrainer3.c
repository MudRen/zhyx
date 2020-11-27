#include <ansi.h>
inherit NPC;
void create()
{
        set_name(HIM"��ӥ"NOR, ({ "hawk" }) );
        set("gender", "����" );
        set("title",HIM"��Į��ӥ"NOR);
        set("age", 32);
        set("long","һ�����԰���ѵ��(train)�Ĺ��ˣ�����\n");
        set("combat_exp", 500000);
        set("attitude", "friendly");
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
                        say( "��ӥ˵������λ" + RANK_D->query_respect(ob)
                                + "�������ҿ����ɣ�\n");
                        break;
               
        }
}

int do_train(string arg)
{
        object me,pet,gold;
        int cost;
        string which;
        me = this_player();
        if(me->is_busy())
        return notify_fail("����һ��������û����ɡ�\n");
        if(!arg) return notify_fail("��ӥ��������Ҫʲôѽ����\n");
        pet = present(arg,environment());
        if(!objectp(pet)) return notify_fail("��ӥ��������Ҫʲôѽ����\n");
        if(pet->query("possessed") != me )
        return notify_fail("��ӥ�������Ǻ�������İɣ���\n");
        switch (random(7)){
        case 0: which = "int"; break;
        case 1: which = "con"; break;
        case 2: which = "per"; break;
        case 3: which = "tol"; break;
        case 4: which = "str"; break;
        case 5: which = "dex"; break;
        case 6: which = "kar"; break;
        
                        }       
//okey we identified the target, now the cost:
        cost = (int) pet->query(which) ;
        cost *= cost;
        if (me->query("balance") < cost*10000)
                return notify_fail("������û��"+chinese_number(cost)+"�����ӡ�\n");
        if((int)me->query("score") < cost)
        return notify_fail("��Ľ�����������"+chinese_number(cost)+"�㡣\n");
        pet->add(which,1);
        pet->save();
        me->add("balance",-cost*10000);
        me->add("score",-cost);
        command("say ���ˣ�\n");
        return 1;
}

