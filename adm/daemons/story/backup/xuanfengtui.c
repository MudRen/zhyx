#include <ansi.h>

void create()
{
        seteuid(getuid());
}

object book = find_object("/clone/lonely/book/xuanfengtui");

object get_owner()
{
    object owner;
    if(objectp(book)) {
        owner = environment(book);
        if(owner->is_character()) return owner;
    }
    return 0;
}

object book_owner = get_owner();
nosave string book_owner_name = (objectp(book_owner) && userp(book_owner)) ? book_owner->query("name") : "ĳ��";

int do_rumor(string arg)
{
    CHANNEL_D->do_channel(this_object(), "rumor", arg);
    return 1;
}

int get_book()
{
    if(objectp(book)) destruct(book);
    if(objectp(book_owner) && userp(book_owner)) book_owner->unconcious();
    do_rumor("��˵" + book_owner_name + "����ʧ��������ɨҶ�ȷ����ӽ���·�ߵ������䣡");
    return 1;
}

nosave mixed *story = ({
        "��ҩʦ���ض������������г����������͵ѧ���һ���������ɨҶ�ȷ������ǿɺޣ�",
        "���أ������װ������ý������ᵽ����ɨҶ�Ⱦ��¡�",
        (: do_rumor, "�������ԣ������һ������ţ���ӭ��·��ʿǰ���۹����Ρ�" :),
        "�һ���",
        "�οͼף��һ�Ӱ����񽣣��̺����������",
        "�ο��ң���Ȼ��ɫ������",
        "���أ�ʵ�˾Ӽ����εı���֮����",
        "�һ����ڵ�����ʩ��������ɨҶ�ȣ�",
        "�οͣ���λ�����ڱ��ݽ�Ŀô��",
        "���أ�������λ��֪�����һ����ϱ���һ���һ���������������ǻ��꣬��ɨ�������ǲ��ף�",
        "���أ�Ϊ�ˣ��ҵ������⿪�����һ���ר��ɨ����ѧ��������ɨҶ�ȣ�",
        "���οͣ�����ԭ���Ǵ�ɨ�����ġ�",
        "���أ��ԣ������������������һ���������˵ıر���ѧ��",
        "��ҩʦ���ڵ����ε�......",
        "���պ󣬽�����",
        "·�˼ף�����û�����Ǹ�������ɨҶ�ȵġ�",
        "·���ң���ȥ��������������ɨ�صġ�",
        "·�˱���ɨ��Ҳ��һ�ݺ���ǰ;��ְҵ�������ﶼ��Ҫ�������¸ڰ���",
        book_owner_name + "��������ɨҶ�ȣ�ɨ�أ�����",
        (: get_book :),
});

string prompt() { return HIW "���������¡�" NOR; }

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}
