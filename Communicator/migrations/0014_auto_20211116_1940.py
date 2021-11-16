# Generated by Django 3.2.8 on 2021-11-16 16:40

import datetime
from django.conf import settings
from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        migrations.swappable_dependency(settings.AUTH_USER_MODEL),
        ('Communicator', '0013_auto_20211110_1301'),
    ]

    operations = [
        migrations.AlterModelOptions(
            name='event',
            options={'ordering': ['-data_create']},
        ),
        migrations.AddField(
            model_name='event',
            name='owner',
            field=models.ForeignKey(default=1, on_delete=django.db.models.deletion.CASCADE, related_name='events', to=settings.AUTH_USER_MODEL),
        ),
        migrations.AlterField(
            model_name='event',
            name='data_create',
            field=models.DateTimeField(default=datetime.datetime(2021, 11, 16, 19, 40, 13, 860758)),
        ),
    ]