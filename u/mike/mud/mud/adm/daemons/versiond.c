// versiond.c

#include <ansi.h>
#include <runtime_config.h>
#include <getconfig.h>
#include <net/socket.h>

// #pragma optimize
// #pragma save_binary

inherit F_DBASE;
inherit F_SAVE;


// Ϊһ���ļ����ӱ�֤�����ļ���ID
int append_sn(string file)
{
        string ckey;
        string text;
        int len;

        switch (file_valid(file))
        {
        case 0:
                // Ŀǰ�ļ��� ID �Ǵ����
                text = read_file(file);
                len = strsrch(text, "\n");
                text = text[len + 1..<1];
                write_file(file, text, 1);

                // ɾ������ID�Ժ��������ִ��

        case -2:
                // Ŀǰû�м���ID
                ckey = file_crypt(file);
                text = read_file(file);
                text = sprintf("// SN:%s\n%s", ckey, text);
                write_file(file, text, 1);
                return 1;

        case -1:
                // û������ļ�
                return -1;

        default:
                // �Ѿ�������ȷ�ļ���ID
                return 1;
        }
}
