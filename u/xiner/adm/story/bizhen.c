// story:bizhen �������ѧϰ��������

#include <ansi.h>

static string char_id;
static string char_name;
mixed give_gift1();
int   give_gift2();
object select_character();

static mixed *story = ({
/*        "ֻ�����Ǻ��¸߸���ŭ�ȣ������ͨ�����Ǿ��Ʋ���������������",
        "���ͨ����һ����˫�ַ�ִ��ǯ���ɣ�������ǯ���˿����������һ���йٱʡ�",
        "���ͨ���һ����������Ⱥ��˫��ʹ��������ȡ��Ѩ������һ��������Ȼռ�����Ϸ硣",
        "������������վ��һ���������ߣ�˫�ֲ������䣬��������������භ��",
        "Ƭ��֮�󡭡���",
        "ֻ����������һ���죬�Ǹ߸�˫������ʵʵ�Ļ������ͨ�ؿڣ�Ҳ��֪���˶��ٸ��߹ǡ�",
        "�������߼�״���ķ�����ǰ��ץ�����ͨ�����ӣ�������ͣ�˺�����",
        "��������üͷ΢�壬�ȵ������������·���ϸϸ�Ѳ顣��",
        "��������Ӧ�������ǣ���������ȥ���ͨ��������ֻ�������ϳ���֮�¸���һ��������",
        "�������º���Ѹ�ٴ򿪰��������������а�����������Ю�־��������һ����ɫ���䡣",
        "��������ŭ�����������̵ģ�ƭ�˵����⣬���ÿ��ˣ��쵽������ȥ����",
        "ʮ�������º����ֽ����ձ��ֻ꣬��Ǻ�Ǻॣ��������������Ρ�ȫ����ˤ�˳�����",
        "����ʱ��֮�����˽��ձ���ǽ�ڡ���ͷҲ�����ˡ�",
        "��ʱ�����ѽ��ձ��������˸��췭�ظ��������µ�שҲ��һ��������������",
        "�������߼���Ҳ�鲻��ʲô���ȵ������նӣ��� ",
*/        "�������������������������𣬼�ʮ������Ƭ�̼����˸��ɸɾ�����",
        "��������",
        "����ʱ����$Nսս�����Ĵӷ�����������������������һƬ�Ǽ���",
	"$N��������û�뵽�⽭����Ȼ������ա����һ�ɽ������������ɽ�ɡ���",
        (: give_gift1 :),
        "˳�����ͨ���ֵķ�����ȥ��$Nֻ������������֮����һ���ձ���",
        "$N�����ǿ��ձ�������һ�����������в��ź������һ����Ƭ��",
        "$N��ʱ����һ�£����ְ������һ��������˳������Ƭ����ȥ������һ����������Ϊ���ء�",
        "$N���п�ϲ���ĵ�������������ǽ����д��ŵ�������벻�����վ����ҵõ�����",
        "�ഫ�ִ��������ߣ�ֻҪ���ֽ����Ħ���ʿл�̿����У���������������κ����顣",
        "$N�ĵ������˵ز��˾������������л�̿�ȥ����˵�գ���ȻƮʧ��ҹĻ�С�",
        (: give_gift2 :),
});

void create()
{
        seteuid(getuid());
        if (! objectp(select_character()))
        {
        	STORY_D->remove_story("bizhen");
                destruct(this_object());
                return;
        }
}

string prompt() { return HIR "�����ִ��š�" NOR; }

object select_character()
{
        object *obs;
        object ob;
        obs = filter_array(all_interactive(), (: ! wizardp($1) &&
                                                 living($1) &&
                                                 $1->query_skill("bizhen-qingzhang", 1) < 1 &&
						 $1->query("combat_exp") > 100000 &&
						 ! $1->query("doing") :));
        if (! sizeof(obs))
                return 0;
        ob = obs[random(sizeof(obs))];
        char_id = ob->query("id");
        char_name = ob->name(1);
        return ob;
}

mixed query_story_message(int step)
{
        mixed msg;

        if (step >= sizeof(story))
                return 0;

        msg = story[step];
        if (functionp(msg)) msg = evaluate(msg);
        if (stringp(msg))
        {
                msg = replace_string(msg, "$N", char_name);
                msg = replace_string(msg, "$ID", char_id);
        }
        return msg;
}

mixed give_gift1()
{
        object ob;
        ob = find_player(char_id);
	if (ob->query("sun/skill/bizhen") || random( 520 - ob->query("kar") * 10 ) > 0 )
        {
	        CHANNEL_D->do_channel(this_object(), "rumor", "��˵" + ob->name(1) +
                              "�п��ڽ������գ�����Ŭ��������");
        	STORY_D->remove_story("bizhen");
                return 0;
        }
        return "˼����$NͻȻ�������ͨ��ʬ�壬���ֵ�����צ״���ƺ�����ǰ��Ҫץȡʲô��";
}

int give_gift2()
{
        object ob;
        object book;

        ob = find_player(char_id);
        if (! ob) return 1;
        ob->set("sun/skill/bizhen", 1);
        tell_object(ob, HIC "��õ��������\n" NOR);
        CHANNEL_D->do_channel(this_object(), "rumor", "��˵������������" + ob->name(1) +
                              "�����");
        book = new("/d/tulong/tulong/obj/xuantie-ling");
        book->move(ob, 1);
        STORY_D->remove_story("bizhen");
        return 1;
}