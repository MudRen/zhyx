#include <ansi.h>

void create()
{
        seteuid(getuid());
}

object book = find_object("/clone/lonely/book/zhenjing1");

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

string get_book()
{
    if(objectp(book)) destruct(book);
    if(objectp(book_owner) && userp(book_owner)) book_owner->unconcious();
    return book_owner_name + "����ҩʦ�����ˡ�";
}

nosave mixed *story = ({
        "�һ���ɽ��",
        "��ҩʦ������ͯ����˵������" + book_owner_name + "�õ��˾����澭�ϲᣡ�㲻��˵�澭�ϲ�һֱ������ô��",
        "�ܲ�ͨ��Ŷ����ô�������ܰ�......",
        "��ҩʦ����ƭ������ô�ã���Ȼ���澭���˱��ˣ��������ҵı̺�����������",
        "�ܲ�ͨ���ȵȣ������Ҷ���ʹ��",
        "��ҩʦ����#����%",
        "�ܲ�ͨ������а�����������㣡�澭��Ļ������⣡��",
        "��ҩʦ�����ó����������ƣ�",
        "�ܲ�ͨ�����У����ó���������ˣ�",
        "��ҩʦ���ҿ�������͸����ˣ�����һͬ��ȥ���������ҷ����澭�ڱ�������ߺ�~",
        "�ܲ�ͨ����ô����",
        "��ҩʦ���Ҿ������㣡",
        "�ܲ�ͨ��......�����������ͣ��ޣ����Ӯ���𣿣�",
        (: do_rumor, "��ҩʦ���ܲ�ͨΪ�����澭�����һ���......" :),
        "�����",
        (: get_book :),
        "��ҩʦ����Σ�����Ǵ��������ѳ����澭������",
        "�ܲ�ͨ���������£��������������鰡����",
        "��ҩʦ��" + book_owner_name + "�������ܣ�����",
        book_owner_name + "���룺�Ҷ�����3�죬���������飬��ο����������飿����������",
        "��ҩʦ�������£���������飡��",
        "�ܲ�ͨ����͵�֣��澭ԭ����ͱ��һ��ˣ����ڵĶ�����Ĭд�����ģ�\n"
        "�Ҷ��ò�֭д��ֽ�ϣ�һ����3����ּ�����ʧ���������а���ƹ������Ǻ��ҵ�ϴ��ˮ��",
        "����а���ã�ֻҪ�澭���ڱ���������У����һ��һ�����",
        "�ܲ�ͨ����......��#��%",
});

string prompt() { return HIW "���������¡�" NOR; }

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}
