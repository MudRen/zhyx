#include <ansi.h>

void create()
{
        seteuid(getuid());
}

object book = find_object("/clone/lonely/book/zhenjing2");

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
static string book_owner_name = (objectp(book_owner) && userp(book_owner)) ? book_owner->query("name") : "ĳ��";

string get_book()
{
    if(objectp(book)) destruct(book);
    if(userp(book_owner)) book_owner->unconcious();
    return book_owner_name + "����ȥץ�����澭~";
}

int do_rumor(string arg)
{
    CHANNEL_D->do_channel(this_object(), "rumor", arg);
    return 1;
}
static mixed *story = ({
        "�����磺����������ô���ú��������׹�צ�ˣ�",
        "÷���磺�㻹˵...�㻹˵...�㲻�����ˣ�",
        "÷���磺�㲻֪����������������?�˼�С��˵�ҵ�ָ�׳�ɫ����,���ǰ׹�צ���ġ�",
        "�����磺......",
        "�����磺��...�Ǳ��澭�أ�",
        "÷���磺������...Ŷ�ϴ���ͷ����ʱ����㷭���������û����ˡ�",
        "��������°�ĭ�����˹�ȥ����������....�ܼ���....��",
        (: do_rumor, "\"ͭʬ\" �������س�����..." :),
        book_owner_name + "�����±ߡ�",
        book_owner_name + "���ӵ���Ӧ���Ҳ������˰ɣ���ץ��ʱ��������",
        book_owner_name + "�����������澭��Ȼ��������ϧֻ���±�.......",
        "�����磺�ߺ�.........",
        book_owner_name + "���ۣ���ѽ������",
        "�����磬" + book_owner_name + "�����������澭����������",
        (: get_book :),
        (: do_rumor, book_owner_name + "Ϊ�˾����澭�����������£�ˤ���ˡ�" :),
});

string prompt() { return HIW "���������¡�" NOR; }

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}
