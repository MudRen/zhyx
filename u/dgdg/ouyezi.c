// ouyezi.c ŷұ��
// Created by Lonely@nitan(1)

#include <ansi.h>

inherit KNOWER;

private int     ask_me();
int  start_work(object me, object ob);       // ��ʼ����
int  prepare_upgrade(object me, object ob);     // ��ʼ����
int  do_help(string arg);
int  do_show(string arg);
void time_out(object me, object ob);

mapping need;
// �����Ǹ����ȼ�����������Ҫ�Ĳ���
mapping need1 = ([
        "/clone/fam/item/baxian" : 1,
        "/clone/fam/item/baxian"    : 2,
        "/clone/fam/item/baxian"      : 2,
        "/clone/fam/item/baxian"       : 2,
]);
mapping need2 = ([
        "/clone/fam/item/baxian"   : 1,
        "/clone/fam/item/baxian"   : 3,
        "/clone/fam/item/baxian"    : 3,
        "/clone/fam/item/baxian"     : 3,
]);
mapping need3 = ([
        "/d/item/obj/wlshongm"   : 1,
        "/d/item/obj/ziyawus"    : 4,
        "/d/item/obj/qicais"     : 4,
        "/d/item/obj/donglings"  : 4,
]);
mapping need4 = ([
        "/d/item/obj/tiancs"     : 1,
        "/d/item/obj/tanxiangm"  : 1,
        "/d/item/obj/donghais"   : 5,
        "/d/item/obj/qingjins"   : 5,
]);
mapping need5 = ([
        "/d/item/obj/wujins"     : 1,
        "/d/item/obj/zitanm"     : 1,
        "/d/item/obj/lvsongs"    : 6,
        "/d/item/obj/qinghaiy"   : 6,
]);
mapping need6 = ([
        "/d/item/obj/chanhs"     : 1,
        "/d/item/obj/hhtanm"     : 1,
        "/d/item/obj/meihuay"    : 7,
        "/d/item/obj/shoushans"  : 7,
]);
mapping need7 = ([
        "/d/item/obj/longyanm"   : 1,
        "/d/item/obj/shuims"     : 1,
        "/d/item/obj/gaos"       : 4,
        "/d/item/obj/mubians"    : 4,
        "/d/item/obj/dushany"    : 4,
        "/d/item/obj/kongques"   : 4,
        "/d/item/obj/moy"        : 4,
]);
mapping need8 = ([
        "/d/item/obj/fenghuangm" : 1,
        "/d/item/obj/wangtianm"  : 1,
        "/d/item/obj/butian"     : 1,
        "/d/item/obj/huangdis"   : 4,
        "/d/item/obj/kunluny"    : 4,
        "/d/item/obj/zdhongs"    : 4,
        "/d/item/obj/yangzhiy"   : 4,
        "/d/item/obj/ganlans"    : 4,
        "/d/item/obj/hujings"    : 4,
]);
void create()
{
        set_name("ŷұ��", ({ "ouye zi", "zi" }));
        set("nickname", RED "���Ľ���" NOR);
        set("gender", "����" );
        set("age", 1000);
        set("long",     
                "��ͷ�ϰ���ͷ�����Ƴ���Ʈ����ǰ����Ŀ���ݵ������й⣬\n"
                "��Ŀ��������˸˸���ž��������ݵĽ��⣬�����ƺ�����Χ\n"
                "��һ�ɽ���֮�С��ԴӸɽ���Īа�ĸ��������͸����������ˡ�\n");
        set("str", 250);
        set("shen_type", 0);

        create_family("������", 1 ,"����");
        set("combat_exp", 250000);
    
        set("attitude", "peaceful");
        
        set("inquiry", ([
                "����" : "���Ѿ��ܾúܾ�û�������ˣ��㻹�����ұ��˰ɡ�\n",
                "����" : (: ask_me() :),
                "����" : (: ask_me() :),
        ]));
        
        setup();
        set("chat_chance", 3);
        set("chat_msg", ({
                "ŷұ�Ӹ������裺��������⣬�����͡����������⣬��Ӣ�ۣ�\n",
                "ŷұ�ӵ�ͷ�������ƺ���˼��ʲô��\n"
                "ŷұ��̾��һ�����������Ӣ�ۣ���Ӣ�ۡ�����������\n"
        }));
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}

void init()
{
        add_action("do_show", "show");
        add_action("do_help", "help");
        add_action("do_help", "����");
        add_action("do_summon", "summon");
}

private int ask_me()
{
        message_vision("$N��$n˵����" 
                "����Ҫ�����Լ��ķ�����\n"
                "���������Ϊ���������ϴ���(cloth)֮��ķ��ߡ�\n"
                "���ȸ�����һ�����ƽ�Ȼ��ѷ��߸��ҿ���(show)��\n",
                this_object(), this_player());
        this_player()->set_temp("upgrade/money", 100000000);
        return 1;
}

int do_summon(string arg)
{
        if (! wizardp(this_player()))
        {
                command("say ��������ǰϹץ��ʲô���������ȥ��");
                return 1;
        }

        return 0;
}

int accept_object(object me, object ob)
{
        string *obj;
        mapping needs;
        int i;

        if (query_temp("upgrade/making")) 
        {
                message_vision("$N��$n˵����������æ���أ����Ե�һ�ᣡ\n",
                               this_object(), me);
                return 0;
        }
                
        if (ob->query("money_id"))
        {
                if (! me->query_temp("upgrade/money"))
                {
                        message_vision("$N��$n�ݹ�ȥ��" + ob->name() +
                                       "���˻����������޹�����»��\n",
                                       this_object(), me);
                        return 0;
                }

                if (ob->value() < me->query_temp("upgrade/money"))
                {
                        message_vision("$N��$n˵���Բ����Ϸ���һ"
                                       "ǧ����������û�д���ۿۡ�\n",
                                       this_object(), me);
                        return 0;
                }

                message_vision("$N��$n˵�����ã�����Ͱ����Ҫ�����ķ��߸��ҿ���(show)�ȡ�\n",
                               this_object(), me);

                me->set_temp("paid/ŷұ��", 1);
                destruct(ob);
                return -1;
        }
        
        if (! mapp(needs = me->query_temp("upgrade/need")) 
        &&  ! me->query_temp("upgrade/prepare"))
        { 
                message_vision("$N��$n˵������������ʲô����\n",
                               this_object(), me);
                return 0;
        }
        
        if (ob->query("armor_type") == "cloth" && ob->is_item_make()
        &&  ob->item_owner() == me->query("id"))
        {       
                if (me->query_temp("upgrade/prepare"))
                {
                        me->delete_temp("upgrade");
                        start_work(me, ob);
                        return 1;
                } else 
                {
                	message_vision("$N��$n˵������������ʲô����\n",
                               	       this_object(), me);
                        return 0;
                }
        }
        
        obj = keys(needs);
        for (i = 0; i < sizeof(obj); i++) 
        {
                if (ob->short() == obj[i]->short()) 
                {               
                        needs[obj[i]] = needs[obj[i]] - 1;
                        if (needs[obj[i]] < 1) 
                        {
                                map_delete(needs, obj[i]);
                        }
                        
                        me->set_temp("upgrade/need", needs);
                        if (! mapp(needs = me->query_temp("upgrade/need")) || sizeof(keys(needs)) < 1)
                        {
                                me->set_temp("upgrade/prepare", 1); 
                                me->delete_temp("upgrade/need");
                                tell_object(me, HIR "\n�������ߵ���Ʒ���ˣ����ڰ����Ҫ�����ķ��߸��Ұɣ�\n" NOR);
                        }
                        destruct(ob);                   
                        tell_object(me, HIR "\n������������û���ˣ���\n" NOR);
                        return -1;
                } else
                {
                    message_vision("$N��$n˵������������ʲô������Ҫ���ҵĲ��ϲ��������\n",
                                   this_object(), me);
                        return 0;
                }
        }
}

int start_work(object me, object ob)
{
        remove_call_out("prepare_upgrade");
        call_out("prepare_upgrade", 1, me, ob);
        set_temp("upgrade/making", ob);
        set_temp("upgrade/player", me);
        ob->set_temp("upgrade/player_id", me->query("id"));
        me->set_temp("upgrade/status", "waiting");
        return 1;
}

int prepare_upgrade(object me, object ob)
{       
        message_vision(HIC "\n$N˵�����ã���¯������\n\n" NOR, this_object());
        message_vision(HIM "$N���˿����е���Щ��������Ҫ����Ʒ" +
                       HIM "�����ְ���������¯�ڣ���ʱ\n����Щ��Ʒ" + 
                       HIM "�ѱ���¯�е�����" HIR "����" HIM "��û��" +
                       "$N������¯����˵����\n���֮����Ϊ��Ѫ������"
                       "��֮�����������......\n\n" NOR , this_object());
        remove_call_out("work_step_1");
        call_out("work_step_1", 5, me, ob);
        return 1;
}

private int work_step_1(object me, object ob)
{               
        message_vision(HIG "¯�𽥽���ת������ɫ�����粻����Ծ��ŷұ���������ص�ע��"
                       "��¯����Ʒ�ı仯��\n\n" NOR, this_object());
        if (objectp(me) && environment(me) == environment())
        {
                me->set_temp("upgrade/can_help", 1);
                message_vision(HIW "$N��$n˵����������"
                               "Ҫע�����Լ��ľ���Ѫ������"
                               "��(help)��һ��֮����\n\n", this_object(), me);
        }
        remove_call_out("time_out");
        call_out("time_out", 30, me, ob);
        return 1;
}

private int work_step_2(object me, object ob)
{
        message_vision(RED "¯�𵭵��İ������������ֳ�һƬ��ɫ......\n\n" NOR, this_object());
        remove_call_out("work_step_3");
        call_out("work_step_3", 3, me, ob);
        return 1;
}


private int work_step_3(object me, object ob)
{
        if (! objectp(ob))
        {
                delete_temp("upgrade"); 
                return notify_fail("ŷұ����Ϊһʱ�Ҳ���Ҫ�������ߣ�����������;���ϣ�\n");
        }
        
        if (! objectp(me))
                me = find_player(ob->query_temp("upgrade/player_id"));

        if (! objectp(me) || environment(me) != environment())
        {
                message_vision(HIW "$N̾�˿�����˵��������Ϊ�����ȥ"
                               "�ˣ������˰��ˣ������ˣ�ȥ�ɣ�\n"
                               "$N�������ĵ����׽���¯���ʹ˲�����\n\n" NOR,
                               this_object());
                if (objectp(me))
                        me->delete_temp("upgrade");

                if (objectp(ob) && present(ob, this_object()))
                        destruct(ob);

                delete_temp("upgrade");
                return 1;
        }
                
        message_vision(HIW "$N���ִӻ���ȡ����һ���ܹ��ϵ�һ��ƿ�ӣ���¯�е�����һЩ����\n" +
                       HIW "��֪�������ʣ�$N���ֽ�" + ob->short() + HIW + "����¯�С�����" +
                       HIW "�ģ�¯�з�\n��������ı仯���������صĹ�â��\n\n" NOR,
                       this_object());
        ob->armor_upgrade(me);
        remove_call_out("work_step_4");
        call_out("work_step_4", 2, me, ob);
        return 1;
}


private int work_step_4(object me, object ob)
{
        if (! objectp(ob))
        {
                delete_temp("upgrade"); 
                return notify_fail("ŷұ����Ϊһʱ�Ҳ���Ҫ�������ߣ�����������;���ϣ�\n");
        }
                
        message_vision(HIW "$N�����Ĵ�¯�г���������õ�" + ob->short() +
                       HIW "���˿��������˵���ܺã��ܺá�\n\n" NOR,
                       this_object());
        remove_call_out("work_step_6");
        call_out("work_step_5", 2, me, ob);
}

private int work_step_5(object me, object ob)
{
        object moye;
        int improve;

        if (! objectp(me))
                me = find_player(ob->query_temp("upgrade/player_id"));

        if (! objectp(me) || environment(me) != environment())
        {
                message_vision(HIW "$N̾�˿�����˵��������Ϊ�����ȥ"
                               "�ˣ������˰��ˣ������ˣ�ȥ�ɣ�\n"
                               "$N�������ĵ����׽���¯���ʹ˲�����\n\n" NOR,
                               this_object());
                if (objectp(me))
                        me->delete_temp("upgrade");

                if (objectp(ob) && present(ob, this_object()))
                        destruct(ob);

                delete_temp("upgrade");
                return 1;
        }
        ob->move(me, 1);
        ob->save();
        message_vision("$N�������õ�" + ob->query("name") + "������$n��\n",
                       this_object(), me);
        me->delete_temp("upgrade");
        delete_temp("upgrade");
        return 1;

}

// ����������¯����ߵ��ߵȼ�
// Ҫ�󣺾� >= 180  �� >= 300  ������Ч�ȼ� >= 100  ���� >= 800 ������� >= 1000
// ������ķ� 200 ��������������� 10%
int do_help(string arg)
{
        object me;
        object ob;

        me = this_player();
        if (me->query_temp("upgrade/status") != "waiting")
        {
                return notify_fail("û��ʲôҵ��\n");
        }
        if (! me->query_temp("upgrade/can_help"))
        {
                if (arg) return 0;
                write("���ڲ������æ��ʱ��\n", me);
                return 1;
        }
        if (me->query("potential") - me->query("learned_points") < 5000)
        {
                return notify_fail("���Ǳ�ܲ������������㣬û��ע����ľ���Ѫ����\n");
        }
        if (me->query("jing") < 180 || me->query("max_jing") < 180)
        {
                message_vision(HIR "$N" HIR "��Хһ����˫�ִ���¯�ߣ���������"
                               "������¯��ͻȻ��ǰһ��...\n" NOR, me);
                tell_object(me, RED "��е�����˥�ߡ�\n" NOR);
                me->set("jing", 0);
                return 1;
        }
        me->receive_damage("jing", 180);
        if (me->query("qi") < 300 || me->query("max_neili") < 300)
        {
                message_vision(HIR "$N" HIR "��Хһ����˫�ִ���¯�ߣ���������"
                               "������¯��ͻȻ��ǰһ��...\n" NOR, me);
                tell_object(me, RED "��е��������̡�\n" NOR);
                me->set("qi", 0);
                return 1;
        }
        me->receive_damage("qi", 300);
        if (me->query("neili") < 800 || me->query("max_neili") < 1000)
        {
                message_vision(HIR "$N" HIR "��Хһ����˫�ִ���¯�ߣ���������"
                               "������¯��ͻȻ��ǰһ��...\n" NOR, me);
                tell_object(me, RED "��е������ݽߡ�\n" NOR);
                me->set("neili", 0);
                return 1;
        }
        if (me->query("jingli") < 300 || me->query("max_jingli") < 500)
        {
                message_vision(HIR "$N" HIR "��Хһ����˫�ִ���¯�ߣ���������"
                               "������¯��ͻȻ��ǰһ��...\n" NOR, me);
                tell_object(me, RED "��е���Ԫ�ݽߡ�\n" NOR);
                me->set("jingli", 0);
                return 1;
        }
        message_vision(HIR "$N" HIR "��Хһ����˫�ִ���¯�ߣ�ɲ�Ǽ䣬¯����ڣ�"
                       "һ��" HIW "�׹�" HIR "��ֱ��������\n\n" NOR, me);
        ob = query_temp("upgrade/making");
        me->delete_temp("upgrade/can_help");
        me->delete_temp("upgrade/status");
        remove_call_out("time_out");
        remove_call_out("work_step_2");
        call_out("work_step_2", 6, me, ob);
        me->add("max_neili", -300);
        me->add("max_jingli", -100);
        me->add("neili", -200);
        me->add("jingli", -100);
        return 1;
}

int do_show(string arg)
{
        object money;
        object ob;
        object me;
        int defense_lvl, n, i;
        string *obj;
        string str;
        mapping needs;
        object needob;

        if (query_temp("upgrade/making")) 
                return notify_fail("������æ���أ����Ե�һ�ᣡ\n");
        
        if (! arg)
                return notify_fail("��Ҫ����ʲô������\n");

        me = this_player();
        if (! objectp(ob = present(arg, me)))
                return notify_fail("������û�����ֶ�����\n");
                
        if (ob->query("equipped"))
                return notify_fail("���Ƚ��" + ob->name() + "��װ����˵��\n");

        message_vision("$n�ó�һ" + ob->query("unit") + ob->name() +
                       "��$N˵�������а���...��\n",
                       this_object(), me);

        if (! me->query_temp("paid/ŷұ��", 1))
        {
                command("heihei");
                me->set_temp("upgrade/money", 100000000);
                command("say ��...��ôҲ���е���˼��˼�ɣ���"
                        "˵һ�����ƽ���ô������Ȼ��Щ��Ҳ�����ԡ�");
                return 1;
        }
        
        if (ob->query("armor_type") != "cloth")
        {
                command("say ����������ʲô������ֻ�����������ϴ���֮��ķ��ߡ�");
                return 1;
        }

        if (! ob->is_item_make())
        {
                command("heng");
                command("say ��...��...�ҿ��������˰ɣ�");
                return 1;
        }

        if (ob->item_owner() != me->query("id"))
        {
                command("kick " + me->query("id"));
                command("say ����Ϊ�ҵ����������µİ��������������ģ�");
                return 1;
        }

        if (me->query("can_summon/" + ob->query("id")))
        {
                defense_lvl = ob->armor_level();
                /*
                switch (defense_lvl)
                {
                case 5:
                        need = need1;
                        break;
                case 10:
                        need = need2;
                        break;
                case 30:
                        need = need3;
                        break;
                case 100:
                        need = need4;
                        break;
                case 300:
                        need = need5;
                        break;
                case 1000:
                        need = need6;
                        break;
                case 3000:
                        need = need7;
                        break;
                case 10000: 
                        need = need8;
                        break;
                default:
                        return notify_fail("�������������Ϊ����\n");
                }
                */
                if (defense_lvl == 5) need = need1;
                else if (defense_lvl == 10) need = need2;
                else if (defense_lvl == 30) need = need3;
                else if (defense_lvl == 100) need = need4;
                else if (defense_lvl == 300) need = need5;
                else if (defense_lvl == 1000) need = need6;
                else if (defense_lvl == 3000) need = need7;
                else if (defense_lvl == 10000) need = need8;
                else return notify_fail("�������������Ϊ����\n");
        }
        
        me->set_temp("upgrade/need", need);
        // needs = me->query_temp("upgrade/need");
        if (! mapp(need)) return notify_fail("������˵����⡣\n");
        obj = keys(need);
        
        str = "\n���" + ob->short() + HIG + "�˴�������Ҫ����Ʒ���£�\n\n";
        for (i = 0; i < sizeof(obj); i++)
        {
                needob = new(obj[i]);
                str += sprintf("%-40s ��\t%s%s\n",
                               needob->short(), 
                               CHINESE_D->chinese_number(need[obj[i]]),
                               needob->query("unit"));
                destruct(needob);
        }
        tell_object(me, HIG + str + NOR);
        tell_object(me, "��ǧ��Ҫ�Ǻ��ҽ����ҵĵ���Ʒ������.....\n");
        tell_object(me, "���" + ob->short() + "�����������Ʒ���룬�������Ұɣ�\n");
        me->delete_temp("paid/ŷұ��");
        return 1;
}

void time_out(object me, object ob)
{
        int at_present;

        if (! objectp(me))
                me = find_player(query_temp("upgrade/player_id"));

        if (! objectp(me) || environment(me) != environment())
        {
                command("say ��֣��ղ���λ�����أ���ô������ˣ�\n");
                at_present = 0;
        } else
        {
                command("say �ҿɲ��ܸ�����ţ��´������ɣ�");
                at_present = 1;
        }

        delete_temp("upgrade");
        if (objectp(me))
                me->delete_temp("upgrade");

        if (ob)
        {
                if (at_present)
                        command("give " + ob->query("id") +
                                " to " + me->query("id"));

                if (environment(ob) == this_object())
                        command("drop " + ob->query("id"));
        }
}


void fight_ob(object ob)
{
        ::fight_ob(ob);
        message_vision("$N��Цһ��������������ͷ��ʲô�˶��С���˵������һָ$n��\n",
                       this_object(), ob);
        ob->unconcious();
}

int accept_fight(object who)
{
        command("say û��Ȥ��");
        return 0;
}

int accept_ansuan(object who)
{
        return notify_fail("����밵�㣬������ǰһ��������̫�����\n");
}

void receive_damage(string type, int n)
{
        return;
}

void receive_wound(string type, int n)
{
        return;
}
