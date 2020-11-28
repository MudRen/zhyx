// story:shenzhao ��Ѫ��צ

#include <ansi.h>

nosave string char_id;
nosave string char_name;
nosave string family_name;
mixed give_gift1();
int   give_gift2();

object select_character();

nosave mixed *story = ({
        "ֻ���Ǻ��´󺺴�Ц�����������䣬�����ˣ��������������ǽ����������ӣ����������ˣ���",
        "�����ױ�����Ӧ�������ǣ�����Ϲܴ��Ը�����",
        "�Ϲܴ��������ؾ���������ٱ������˲������ٷ��ơ���",
        "һ���ױ�Ц�������Ƕ��ǹϹܴ�������࣬��ƾ�����ĸ���������ȸ��֣���",
        "��ͷ��Ȼ���˺ٺ�һЦ��˵������ƾ�������ˣ�ԭҲû��ȸ��֡���",
        "�����ź���һ���������Էɿ���ֻ��һ�˸��ֱ�����¶΢Ц��",
        "�Ϲܴ�����������ү��������참������˭����",
        "����΢Ц��������̤�����ա���ʱ�����������ı������ִ��ķ����䡣",
        "�����������䣬�������ƣ��ֱ����������ױ����ؿڣ��������죬�����߹���ϡ�",
        "�Ϲܴ����Ʋ����æ����һԾ���Ӵ���ȱ�������˳�ȥ��",
        "���˱�����ͷ������׷�ϣ�ȴ��һ����������ݣ�����������",
        "������Ʒ��ߣ������ǰ�������Ϲܴ���������һ��������Ѳ��������ģ��������ڵ��ϡ�",
        "���˱��ϰ��ߣ����Ϲܴ��Ѿ�����͸�ˣ�����໥����һЦ��",
        "���˺����������ж����Գ��棬���룺��������˭���书���֮�ߣ������������С���",
        "�����߽����գ��⿪�˻������˵�Ѩ�����ֽ������ױ���ʬ�������˺ӣ��ص����",
        "�˻������˲�ס��л����������������",
        "�����������������ʲų��ɻ������ݼ��������ճ£����ֽ��ϡ�������λӢ�۴�������",
        "����ȴ������Ӣ�۲��ʳ���������֮�ͣ�����ҳݣ���������ܶ���������꣬�����Ѿ��Ի�����˵���ƮȻ��ȥ��",
        "�½��ϵ��������������к��ܣ�ֻ��ϧ�в�֪��������������...��˵�곤����̾�˿�����",
        (: give_gift1 :),
        "�½��Ϲ��˹��֣���������λӢ�ۣ����յ��Լ�ʶ��������֮�߳���Ʒ��֮���У����Ҽ���Ե���β�������������",
        "����΢Ц�����������޵£��񵱡�Ӣ�ۡ����֣�����$F$N�����ɳ��ܶ�����Ц�ˡ���",
        "�½��ϵ����������书��ǿ��������������Ѫ��Ϊ�ɹ󣬽��պ͸���Я��һս�������ޱȡ���",
        "$NЦ���������ܶ����������£�����һ�����书��Ȼ�˵ã���",
        "�½���΢Ц���������������������ˣ����ձ��������һ����ӥ����ͼ��Ϊ���������������Ҫ���°�æ����ƾ�˻��������������ҡ���",
        (: give_gift2 :),
});

void create()
{
        seteuid(getuid());

        if (! objectp(select_character()))
        {
                destruct(this_object());
                return;
        }
}

string prompt() { return HIC "������������" NOR; }

object select_character()
{
        object *obs;
        object ob;

        obs = filter_array(all_interactive(),
                           (: ultrap($1) &&
                              living($1) &&
                              $1->query("combat_exp") >= 5000000 &&
                              $1->query_skill("unarmed", 1) > 300 &&
                              $1->query_skill("ningxue-shenzhao", 1) < 1 &&
                              $1->query("family/family_name") &&
                              $1->query_dex() > 45 &&
                              $1->query("str") > 38 &&
                              $1->query("shen") > 0 &&
                              ! $1->query("story/shenzhao") &&
                              ! wizardp($1) &&
                              ! $1->query("doing") :));
        if (! sizeof(obs))
                return 0;

        ob = obs[random(sizeof(obs))];
        char_id = ob->query("id");
        char_name = ob->name(1);
        family_name = ob->query("family/family_name");
        return ob;
}

mixed query_story_message(int step)
{
        mixed msg;

        if (step >= sizeof(story))
                return 0;

        msg = story[step];
        if (stringp(msg))
        {
                msg = replace_string(msg, "$N", char_name);
                msg = replace_string(msg, "$F", family_name);
                msg = replace_string(msg, "$ID", char_id);
        }
        return msg;
}

mixed give_gift1()
{
        object ob;
        ob = find_player(char_id);
	if (ob->query("story/shenzhao") || random( 550 - ob->query("kar") * 10 ) > 1 )
        {
	        CHANNEL_D->do_channel(this_object(), "rumor", "��˵" + ob->name(1) +
                              "��½���һͬ��ս�ڵУ�����֮����������̵����ꡣ");
                return 0;
        }
        return "�½������룺����������Ϊ��Ե����������񲻿�ϧ�����ɱ�׷�����ˡ�";
}

int give_gift2()
{
        object ob;
        object book;

        ob = find_player(char_id);
        if (! ob) return 1;

        /* if (ob->query_skill("ningxue-shenzhao", 1) < 10)
                ob->set_skill("ningxue-shenzhao", 10); */

        ob->set("story/shenzhao", 1);
        tell_object(ob, HIC "��õ��˲�ӥ����ͼ��\n" NOR);
        CHANNEL_D->do_channel(this_object(), "rumor", "��˵�½��Ͻ�����Я���Ĳ�ӥ����ͼ��Ϊ����������" + ob->name(1) +
                              "��");
        book = new("/u/dgdg/obj/cangying-hua");
        book->move(ob, 1);
        return 1;
}
