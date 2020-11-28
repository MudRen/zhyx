// story:qishangquan ����ȭ

#include <ansi.h>

nosave string char_id;
nosave string char_name;
nosave string family_name;

int give_gift();
object select_character();

nosave mixed *story = ({
        "��˵���ճ�����һ���ָ��־�֮��",
        "���У����������̸ով�����һ����ս������Ӧ�Ȼع������������̡�",
        "���޼ɣ�����ʹ˵��Ҳû����ô�Ҿͺ�����ʹ�Ȼع��������常���ΤһЦȥ׷�������ɡ�",
        "ΤһЦ���ǣ�������",
        "лѷ���޼ɣ���������������������Ҫ���֣�������һ����ȥɱ���͹���ΤһЦ���Ǻ���һ������̰ɡ�",
        "���޼ɣ�Ҳ�ã��常�������������ˡ�",
        "˵�գ����޼ɡ����С�ΤһЦ�����˾�ת�������ȥ�ˡ�",
        "лѷ���룺��Ȼ˵�ҵ��书����ɱ����������......Ӧ��Ҳ����һ����ս���������ˣ�׷��ȥ��˵��",
        "�������ʱ����лѷ�Ѿ�׷���˳���.........",
        "лѷ�ȵ�����������������ܣ�",
        "�����ŵó���һ���亹������һ���������ת��������һ����ֻ��лѷһ�˲�����һ������",
        "��������˵�ҵ�ͽ����ƾ��Ҳ��ɱ���ʦ��ô����˵��Ĺ����кܴ�Ľ������������⼸��Ҳ���ǰ׻��",
        "лѷ���ϻ���˵�����ɣ�����",
        "лѷ˵�վ�������ӳ�һȭ�������ٺ�һЦ����������һת�ͱܿ��ˡ�",
        "лѷ���룺�����ڵ����Ҫɱ������ȷʵ���ף���������ڹ�������Ӧ����ɱ������$N������Ļ����Ǿ�һ��û����",
        "��˵�ܲ٣��ܲپ͵���$N·������һ��лѷ�ͳ�������û��ȣ�������ʩչ�Ṧ�ϵ�лѷ��ߡ�",
        "$N����лѷ˵����л��ǰ�����������ʵ���ҵ�ŵ���ˣ�",
        "��������$N��������ĵı���������˵�����ķ������ӵ�����$N���ޡ���һ����",
        "$N�������û�ð���ɣ���ȫ������һ���������ȥ������",
        "������״�������ԣ�����",
        "����$N�ڹ���񣬳�������þ������ϣ���������󵹷��˳�ȥ",
        "лѷ�������������ϵ������ĺ��棬Ȼ���׼���ĳ������Դ�����Ĳ���һ������ȥ������",
        "�������ж���������һ�������ˣ�������",
        "лѷ�����Ц����������������������������������������",
        "��������......",
        "лѷ����$N˵���������ھͰ��յ����Լ�������ҵ�����ȭ���ڸ��㣡",
        (: give_gift :),
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

string prompt() { return HIY "�����ִ��š�" NOR; }

object select_character()
{
        object *obs;
        object ob;

        obs = filter_array(all_interactive(),
                           (: ultrap($1) &&
                              living($1) &&
                              $1->query_skill("qishang-quan", 1) < 1 &&
                              $1->query("combat_exp") <= 3000000 &&
                              $1->query("combat_exp") > 2500000 &&
                              $1->query("max_neili") > 5500 &&
                              SKILL_D("qishang-quan")->valid_learn($1) &&
                              ! wizardp($1) &&
                              ! $1->query("story/qishangquan") :));
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
        if (stringp(msg))
        {
                msg = replace_string(msg, "$N", char_name);
                msg = replace_string(msg, "$ID", char_id);
        }
        return msg;
}

int give_gift()
{
        object ob;

        ob = find_player(char_id);
        if (! ob) return 1;

        if (ob->query_skill("qishang-quan", 1) < 100)
                ob->set_skill("qishang-quan", 100);

        ob->set("story/qishangquan", 1);
        tell_object(ob, HIC "���лѷ����ѧϰ��������ȭ��\n" NOR);
        CHANNEL_D->do_channel(this_object(), "rumor", "��˵" + ob->name(1) +
                              "��лѷ����ѧϰ��������ȭ��");
        STORY_D->remove_story("qishangquan");
        return 1;
}
