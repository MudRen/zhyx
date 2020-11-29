
#include <ansi.h>

inherit NPC;
inherit F_DEALER;

int ask_reborn();
string ask_chocoGift();
string ask_NationalGift();
string ask_dailyGift();
int ask_biwu();
int ask_lonely();

void create()
{
    set_name(HIG"������"NOR, ({"gift_girl", "gift girl", "girl"}));
    set("title", HIR"��"HIW"����ʹ��"HIR"��"NOR);
    set("gender", "Ů��");
    set("str", 35);
    set("int", 13);
    set("con", 34);
    set("dex", 32);
    set("per", 40);

    set("vendor_goods", ({
                "/d/zhuanshi/obj/zhen",
                "/u/xiner/wash/obj/zhen",
                "/u/kasumi/obj/bathwater",
                "/u/kasumi/obj/herotie",
                "/clone/book/guoshi_book.c",
        }));
    set("max_qi", 80000);
    set("max_jing", 20000);
    set("neili", 60000);
    set("max_neili", 60000);
    set("jiali", 200);

    set("combat_exp", 95000000);
    set_skill("unarmed", 700);
    set_skill("sword", 750);
    set_skill("claw", 700);
    set_skill("strike", 800);
    set_skill("hand", 700);
    set_skill("cuff", 700);
    set_skill("parry", 800);
    set_skill("dodge", 800);
    set_skill("force", 800);
    set_skill("yunv-xinjing", 750);
    set_skill("zhuangzi-wu", 800);
    set_skill("suxin-jian", 1000);
    set_skill("qiankun-danuoyi", 700);
    set_skill("yinyang-shiertian", 800);
    set_skill("martial-cognize", 700);
    set_skill("lonely-sword", 200);
    set_skill("zuoyou-hubo", 400);

    map_skill("parry", "qiankun-danuoyi");
    map_skill("force", "yunv-xinjing");
    map_skill("dodge", "zhuangzi-wu");
    map_skill("unarmed", "yinyang-shiertian");
    map_skill("sword", "suxin-jian");
    map_skill("strike", "liuyang-zhang");
    map_skill("hand", "jiuyin-shengong");
    map_skill("cuff", "jiuyin-shengong");
    map_skill("claw", "jiuyin-shengong");

    prepare_skill("unarmed", "yinyang-shiertian");

    set("inquiry", ([
                "ת��" : (: ask_reborn :),
                "��������" : (: ask_chocoGift :),
                "ÿ������" : (: ask_dailyGift :),
                "��ɽ�۽�" : (: ask_biwu :),
                "���¾Ž�" : (: ask_lonely :),
            ]));

    set("chat_chance_combat", 150);
    set("chat_msg_combat", ({
        (: command("perform unarmed.tian") :),
        (: exert_function, "recover" :),
        (: exert_function, "powerup" :),
    }));

    set_temp("apply/attack", 500);
    set_temp("apply/defense", 300);
    set_temp("apply/damage", 300);
    set_temp("apply/unarmed_damage", 300);
    set_temp("apply/armor", 300);


    setup();

    carry_object("/d/death/obj/weapon60")->wield();

}

void init()
{
    object me;
    ::init();

    add_action("do_list", "list");
    add_action("do_buy", "buy");

    if (interactive(me = this_player()) && !is_fighting())
    {
        remove_call_out("greeting");
        call_out("greeting", 1, me);
    }
}

void greeting(object ob)
{
    object me;
    me = this_player();
    if (!ob || !present(ob, environment()))
        return;
    command("look " + me->query("id"));
    /*command("say С���ѹ������棬ʵ���ǰ����ѵ�һ����������ţ�");
     command("say �������м����书�ؼ��������������ˡ�");
     command("say �Ժ�Ͷ����ƣ�ά�������ƽ�����ξͽ������ˣ���");*/

    return;
}

int ask_lonely()
{
    object me;
    me = this_player();

    if (me->query("int") < 58)
    {
        command("laugh " + me->query("id"));
        command("say �������̻���ѧ���£���¯����ɡ�");
        return 1;
    }

    if (me->query_skill("lonely-sword", 1))
    {
        command("kick " + me->query("id"));
        command("say ѧ���˻�������Ϲ���ڸ���Լ���ȥ��ȥ��");
        return 1;
    }
    else
    {

        if (me->query_skill("dugu-jiujian", 1))
            me->delete_skill("dugu-jiujian");

        me->set("can_learn/lonely-sword/kasumi_boss", 1);

        command("say �ðɣ��Ҿʹ�����¾Ž���");
        /* me->set_skill("lonely-sword", 10); */
    }
    return 1;
}

int recognize_apprentice(object ob, string skill)
{
    if (!ob->query("can_learn/lonely-sword/kasumi_boss"))
    {
        message_vision(CYN "$N" CYN "���˸���������$n" CYN "˵"
                           "�������ֲ�����ʦ����ΪɶҪ���㣿\n" NOR,
                       this_object(), ob);
        return -1;
    }

    if (skill != "lonely-sword")
    {
        command("say ����书���һ��ã�����һ���ࡣ");
        return -1;
    }

    return 1;
}

int ask_reborn()
{
    int n;
    object me;
    object *inv;
    object room;
    me = this_player();

    inv = deep_inventory(me);
    command("look " + me->query("id"));

    for (n = 0; n < sizeof(inv); n++)
    {
        if (!playerp(inv[n]))
            continue;
        else
        {
            command("say �㱳����˭�����������£�");
            return 1;
        }
    }

    if (me->query("reborn"))
    {
        command("say ת�˻�ת����ת�ò���ͷ�ΰ���");
        return 1;
    }

    if ((int)me->query("balance") < 200000000)
    {
        command("say ת����Ҫ�������ƽ�Ĵ��Ŷ����Ĵ���ƺ���������");
        return 1;
    }

    if ((int)me->query_skill("martial-cognize", 1) < 600)
    {
        command("say �����ѧ�������������޷�ת����");
        return 1;
    }

    if ((int)me->query_skill("lunhui-jian", 1) > 1)
    {
        command("say �Բ���ѧ���ֻؽ�������޷�����ת����");
        return 1;
    }

    if (living(this_object()) && present("zhuanshi tongzhi", me))
    {
        room = find_object("/d/zhuanshi/sky/sky1");
        if (!room)
            room = load_object("/d/zhuanshi/sky/sky1");
        me->move(room);
    }
    else
    {
        command("sigh");
        command("say ���õ���֪ͨ�顱��û�У�");
    }

    return 1;
}

string ask_chocoGift()
{
    object me;
    object ob;

    me = this_player();

    if (me->query("gift2015/newyear/get"))
    {
        me->set("reward/gift/choco/get", 1);
        return "Ҫ�˻���Ҫ������̰�ģ�û��������\n";
    }

    if (me->query("reward/gift/choco/get"))
    {
        return "Ҫ�˻���Ҫ������̰�ģ�û��������\n";
    }

    message_vision(HIY "$N�ó�һ���ɿ����ݸ�$n��\n" NOR, this_object(), me);

    ob = new ("/u/kasumi/obj/chocolate");
    ob->move(me, 1);
    me->set("reward/gift/choco/get", 1);

    return "�ðɣ�����ɿ�������ȥ�԰ɡ�\n";
}

// ��������
string ask_dailyGift()
{
    object me = this_player();
    int exp, pot, day, month, year, *date, exp0, exp1;
    string daily;

    date = localtime(time());
    year = date[5];
    month = date[4] + 1;
    day = date[3];

    exp = me->query("combat_exp");

    daily = "reward/daily/" + year + "/" + month;

    if (me->query(daily) == day)
    {
        tell_object(me, HIR "����������Ѿ�Ҫ�������ˣ������������ɡ�\n" NOR);
    }
    else
    {
        // ����ÿ�մ򿨴���
        me->add("reward/record/daily", 1);

        // Ǳ������5K
        pot = exp / 100;
        if (pot < 5000)
            pot = 5000;
        // Ǳ������5��
        if (pot > 50000)
            pot = 50000;

        pot = me->improve_potential(pot);
        if (! me->query("skybook/guard/death"))
            me->set("skybook/guard/death", 1);
        me->set(daily, day);
        message_vision(HIW "$N�����" + chinese_number(pot) + "��Ǳ�ܽ���������������\n" NOR, me);
        me->start_busy(3);
        return "���ˣ���������ˣ���Ϸ���֡�\n";
    }

    return "һ��ֻ����һ������Ŷ��\n";
}

string ask_NationalGift()
{
    object me;
    object ob;

    me = this_player();

    if (me->query("reward/festival/National"))
    {
        me->add("potential", -100000);
        tell_object(me, HIG "�������̰�ģ����۳�ʮ��Ǳ�ܡ�\n" NOR);
        return "Ҫ�˻���Ҫ������̰�ģ���\n";
    }

    me->add("combat_exp", 60000);
    me->add("potential", 600000);
    tell_object(me, HIG "��ϲ������������㾭�����ʮ��Ǳ�ܡ�\n" NOR);
    me->set("reward/festival/National", 1);

    return "������֡�\n";
}

int ask_biwu()
{
    int n;
    object me;
    object *inv;
    object room;
    me = this_player();

    inv = deep_inventory(me);
    command("look " + me->query("id"));

    for (n = 0; n < sizeof(inv); n++)
    {
        if (!playerp(inv[n]))
            continue;
        else
        {
            command("say �㱳����˭�����������£�");
            return 1;
        }
    }

    if (me->query("age") < 18)
    {
        command("say ��δ��18�겻�ܲ�����");
        return 1;
    }

    if ((int)me->query_skill("martial-cognize", 1) < 100)
    {
        command("say �����ѧ����������100�������Ǹ���ᣬ��ɶ���֣�");
        return 1;
    }

    if (living(this_object()) && present("yingxiong tie", me))
    {
        room = find_object("/adm/npc/huashanjueding");
        if (!room)
            room = load_object("/adm/npc/huashanjueding");
        me->move(room);
    }
    else
    {
        command("grin");
        command("say �����Ӣ�������ܲ��������Ǵ���������һ���ɣ�����������Żݣ�");
    }

    return 1;
}

/*
string ask_cake()
{
        object me;
        object ob;

        me = this_player();

        if (me->query("gift2007/mid-autumn/get"))
        {
            return "Ҫ�˻���Ҫ������̰�ģ�û��������\n";
        }

        message_vision(HIY "$N�ó�һ�������±��ݸ�$n��\n" NOR, this_object(), me);

        ob = new("/u/kasumi/mooncake");
        ob->move(me, 1);
        me->set("gift2007/mid-autumn/get", 1);

        return "�ðɣ���������±�����ȥ�԰ɡ�\n";
}


string ask_tianjing()
{
        object me;
        object ob;

        me = this_player();

        if (me->query("gift2007/national-day/get"))
        {
            return "Ҫ�˻���Ҫ������̰�ģ�û��������\n";
        }


        if (me->query("reborn"))
        {
              message_vision(HIY "$N�ó�һ������쾧�ݸ�$n��\n" NOR, this_object(), me);
            ob = new("/d/death/obj/tianjing");
            ob->move(me, 1);
            me->set("gift2007/national-day/get", 1);
            return "�ðɣ�������֣��úü���Ŷ��\n";
        }

                return "��������������ת���ɣ�\n";

}


int recognize_apprentice(object ob, string skill)
{
        if (! ob->query("can_learn/yinyang-shiertian/kasumi"))
        {
                message_vision(CYN "$N" CYN "���˸���������$n" CYN "˵"
                               "�������ֲ�����ʦ����ΪɶҪ���㣿\n" NOR,
                               this_object(), ob);
                return -1;
        }

        if (skill != "yinyang-shiertian")
        {
                command("say �������书�ҿɽ̲����㣬�����Լ���ʦ���ɡ�");
                return -1;
        }

        return 1;
}



int accept_fight(object ob)
{
        if (is_fighting())
        {
                message_vision(CYN "$N" CYN "��$n" CYN "�е������ȱ�"
                               "���Ҵ�����ܾ��������ġ�\n" NOR,
                               this_object(), ob);
                return -1;
        }

        if (ob->query("combat_exp") < 500000)
        {
                message_vision(CYN "$N" CYN "����һЦ����$n" CYN "����"
                               "�㻹���Ȱѹ�����������˵�ɡ�\n" NOR,
                               this_object(), ob);
                return -1;
        }

        if (query("qi") < 5000 ||
            query("jing") < 2000 ||
            query("neili") < 5000)
        {
                message_vision(CYN "$N" CYN "ҡҡͷ��$n" CYN "��������"
                               "��̫���ˣ�����Ъ�����˵�ɡ�\n" NOR,
                               this_object(), ob);
                return -1;
        }

        if (ob->query("can_learn/yinyang-shiertian/kasumi"))
        {
                message_vision(CYN "$N" CYN "��$n" CYN "�����ã�������"
                               "�������档\n" NOR, this_object(), ob);
                return 1;
        }

        message_vision(HIW "$N" HIW "��ϲ�����úúã�����������������"
                       "���Ȼ��Ȼ���\n" NOR, this_object(), ob);

        competition_with(ob);
        return -1;
}


void win()
{
        object ob;
        if (! objectp(ob = query_competitor()))
                return;

        message_vision(CYN "$N" CYN "���˿�$n" CYN "���ٺ�Ц�������ˮ"
                       "ƽ̫���ˣ�Ҫ�ú��������ú�������\n" NOR,
                       this_object(), ob);
        ::win();
}


void lost()
{
        object ob;
        int exp, pot, sc, ww;
        string msg;

        exp = 20000 + random(10000);
        pot = 2000 + random(1000);
        sc = 800 + random(300);
        ww = 800 + random(300);

        if (! objectp(ob = query_competitor()))
                return;

        message_sort(HIW "\n$N" HIW "��ѽһ����Ĩ��Ĩͷ�ϵĺ���ϲ������"
                     "λ" + RANK_D->query_respect(ob) + HIW "������书"
                     "����������ȷ�ǿ���֮�ġ������ɣ��Ҵ�����һ�׾����书��\n" NOR,
                     this_object(), ob);

        tell_object(ob, HIC "\nСϺͬ�⴫���㡸����ʮ���졹��ѧ��\n" NOR);
        ob->set("can_learn/yinyang-shiertian/kasumi", 1);
        ob->improve_skill("martial-cognize", 1500000);

        if (ob->query("potential") > ob->query_potential_limit())
            pot = 1;

        ob->add("combat_exp", exp);
        ob->improve_potential(pot);
        ob->add("score", sc);
        ob->add("weiwang", ww);

        msg = HIC "\nͨ����ε�������������" +
              chinese_number(exp) + "�㾭�顢" +
              chinese_number(pot) + "��Ǳ�ܡ�" +
              chinese_number(sc) + "�㽭��������" +
              chinese_number(ww) + "�㽭��������\n" NOR;

        tell_object(ob, sort_msg(msg));

        ::lost();
}
*/
