// edit.c
// Updated by Lonely

#include <ansi.h>
inherit F_CLEAN_UP;

mixed query(string arg)
{
        if (arg && arg == "channel_id")
                return HIM "�༭��(Edit)";
        return 0;
}

int main(object me, string file)
{
        if (! SECURITY_D->valid_grant(me, "(apprentice)"))
                return 0;
                
        if (! file) return notify_fail("ָ���ʽ��edit <����>\n");
        
        if (in_edit(me)) return notify_fail("���Ѿ���ʹ�ñ༭���ˡ�\n");
        
        file = resolve_path(me->query("cwd"), file);

        foreach (object user in users())
        if (file == "/" + in_edit(user))
                return notify_fail("�����ͻ��" + user->name(1) + "(" + 
                        capitalize(user->query("id")) + ")" + 
                        "���ڱ༭���ļ�(" + file + ")��\n");

        printf("�༭�ļ���%s\n", file);
        CHANNEL_D->do_channel(this_object(), "sys",
                sprintf("%s(%s)���ڱ༭�ļ�(%s)��",
                me->name(1),
                capitalize(me->query("id")),
                file));
                
        seteuid(geteuid(me));
        me->set("cwf", file);
        SECURITY_D->backup_file(file);
        ed(file); 
        
        log_file("static/edit", sprintf("%s %-9s edit %s from %s.\n",
                                        log_time(),
                                        geteuid(me), file,
                                        query_ip_name(me)));
        return 1;
}
int help(object me)
{
        write(@HELP
ָ���ʽ : edit <����>, edit here
���ô�һָ���ֱ�������ϱ༭������
                /��ǰ����ƥ����
                ?�������ƥ����
                =��ʾ��ǰ��������
                a�ڵ�ǰ�еĺ������
                A��'a'����
                c�޸ĵ�ǰ�У��滻��ѯ�ı�
                dɾ��һ�л����
                e����һ���ļ����ǵ�ǰ�ļ�
                E��'e'���ƣ���ֻ���ļ������޸�֮����Ч
                f��ʾ/�ı䵱ǰ�ļ����ļ���
                g��������ƥ�����ִ��ĳ������
                h����
                i�ڵ�ǰ��ǰ�����ַ�
                k��һ���ַ���ǵ�ǰ��
                l�г�һ�л���У��������ַ���
                m�ƶ�һ�л���е�ָ����λ�ã��кţ�
                n����к�
                Oͬ'i'
                oͬ 'a'
                p�г�һ����Χ����
                q�˳�
                Q�˳������Ҳ���
                r���ļ�β����ָ���к���������ļ�
                s�������滻
                set��ѯ���ı��洢ĳ���趨ѡ��
                t����һ�л��е�ָ������
                v�������Բ�ƥ�����ִ��ĳ������
                x���ļ����˳�
                wд�뵱ǰ�ļ�����ָ���ļ������ø���
                W��'w'���ƣ�����׷��
                z��ʾ20�У����� . + - ���ֱ��
                Z��ʾ40�У����� . + - ���ֱ��

HELP
        );
        return 1;
}


