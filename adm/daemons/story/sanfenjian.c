// story:sanfenjian ���ֽ���

#include <ansi.h>

nosave string char_id;
nosave string char_name;
mixed give_gift1();
int   give_gift2();
nosave string family_name;

object select_character();

nosave mixed *story = ({
        "ֻ����������һ��������������˫��һ�С�ָ�컮�ء��������˻���ͩ�ĳ�����",
        "�������˳�һ�����е��������������л�˵����",
        "�ڻ��˱���ǰȥ������ҫ�ۣ��ۼ���Ҫ�����ҵ���ʬ��",
        "����������һ���������ϵĺ첼�����������У�˫�ָ߾٣��е�������������",
        "�ڻ��˾㶼�󾪣����˼�����",
        "�����°��������������Χ���������ѣ�����ֻ��ƾһ����ҵ��ͼ���ҡ�",
        "�����¼�Цһ����˵�������������Ҫ�ж�ȡʤ�����Ƚ�����������ˡ���",
        "����ͩ�������ã����Һ��㵥�������������ֵĸ��С���",
        "����ͩ˵�ս���ƫ�棬б����硣�����µ�˫�������������������ܡ�����ת˲�����߰��С�",
        "ֻ��һ�����У������������н������ַ��ϰ�գ����˲�Լ��ͬ�������Ȳʡ�",
        "����������ɳ����࣬˵�������������ˣ�������㣡������ȥ�ⱳ�Ϻ첼������",
        "����ͩ�������������ϼ������������ʣ�˫��ȥ���ⲿ�������˷�Ϊʥ��ġ�����������",
        "��������ɫһ�����ȵ�������ȥ��������һ�ͻȻ���ѷ�׶�������ؼ��ɶ�����",
        "��һ�±�����䣬����ͩ���Ա��ã�����һ���������š���ȫ���ֱ����䵹�����˿�ȥ��",
        "������һ�����������ݣ����ѷ�׶�����֣�������������������������",
        "����ͩ˫�����죬����������Ȼ�����������˾��Ծ�ŭ������������",
        "����ͩ��ͦ������ֻ���ö���������������������׶������������£����ڽűߡ�",
        "����ͩ����������������ȣ����ѷ�׶�Ѿ��������Լ�Ҫ����",
        "�����º������ϣ������転�������ֶ�׼����ͩ��ͷ���¡�",
        "ֻ�������µ������ֽ���ѹ�����ͩͷ�ϣ�����������������ñ�ϴ���",
        "������Ҫ��ǰԮ�֣���Ȼ�����һ��������ͩ���ֶ̽��˵�һ���������������ظ�֮�䡣",
        "�����´��һ�������㵹���������Ǻ���ۺ�һ���ʡ�",
        "����ͩתͷ��ȥ����δ���ü�������Ӱ��һλ�����˱�ͷҲ���ص�ƮȻ��ȥ��",
        (: give_gift1 :),
        "����ͩʩչ�Ṧ���ɱ����ߣ�һ�ߺ���������Ī�ߣ�",
        "�������Զ��˶٣�ͣ�½Ų�����һ�ᣬ����ͩ�����������",
        "����ͩ�������ж������СŮ�������м���֣����ʶ������մ�������",
        "$N����һЦ��˵����������$F��$N��ŮӢ�������ˡ���",
        "$N�ֵ�����������ɽ˫ӥ��λǰ�����ֽ����ھ���ʱ�����յü������񼼣������������顣��",
        "����ͩ���������������ȣ�����Ϊ����ֻ�ܽ�������Я���ļ�ë����Ϊ���������㡣��",
        "����ͩ�ֵ�������������Ե�����տɳִ���������ɽ���ң��Ҷ������׽�����ȫ���������㡣��",
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
                              $1->query("combat_exp") >= 2500000 &&
                              $1->query_skill("sword", 1) > 300 &&
                              $1->query_skill("sanfen-jianshu", 1) < 1 &&
                              $1->query("dex") > 38 &&
                              $1->query("family/family_name") &&
                              ! $1->query("story/sanfenjian") &&
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
	if (ob->query("story/sanfenjian") || random( 550 - ob->query("kar") * 10 ) > 1 )
        {
	        CHANNEL_D->do_channel(this_object(), "rumor", "��˵" + ob->name(1) +
                              "���д����緶������������������");
                return 0;
        }
        return "����ͩ���룺�ղŴ��������������������������ԭ����������������������֪���������񲻳ɽ���Ц����";
}

int give_gift2()
{
        object ob;
        object book;

        ob = find_player(char_id);
        if (! ob) return 1;

        /* if (ob->query_skill("sanfen-jianshu", 1) < 50)
                ob->set_skill("sanfen-jianshu", 50); */

        ob->set("story/sanfenjian", 1);
        tell_object(ob, HIW "��õ��˼�ë�š�\n" NOR);
        CHANNEL_D->do_channel(this_object(), "rumor", "��˵����ͩ�Ѽ�ë���͸���" + ob->name(1) +
                              "��");
        book = new("/u/dgdg/obj/jimao-letter");
        book->move(ob, 1);
        return 1;
}
