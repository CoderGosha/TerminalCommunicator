# Generated by Django 3.2.8 on 2021-11-10 10:01

import datetime
from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('Communicator', '0012_auto_20211103_2223'),
    ]

    operations = [
        migrations.AlterField(
            model_name='event',
            name='data_create',
            field=models.DateTimeField(default=datetime.datetime(2021, 11, 10, 13, 1, 44, 954454)),
        ),
        migrations.AlterField(
            model_name='event',
            name='event_type',
            field=models.IntegerField(choices=[(0, 'Exec'), (1, 'Http Get')], default=0),
        ),
    ]
