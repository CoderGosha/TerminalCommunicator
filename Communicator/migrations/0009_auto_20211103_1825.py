# Generated by Django 3.2.8 on 2021-11-03 15:25

import datetime
from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('Communicator', '0008_auto_20211103_1824'),
    ]

    operations = [
        migrations.AlterField(
            model_name='event',
            name='data_completed',
            field=models.DateTimeField(blank=True, null=True),
        ),
        migrations.AlterField(
            model_name='event',
            name='data_create',
            field=models.DateTimeField(default=datetime.datetime(2021, 11, 3, 18, 25, 37, 690742)),
        ),
    ]
