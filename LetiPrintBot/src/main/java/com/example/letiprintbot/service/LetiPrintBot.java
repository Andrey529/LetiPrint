package com.example.letiprintbot.service;

import com.example.letiprintbot.config.BotConfig;
import com.example.letiprintbot.httpClient.HttpController;
import lombok.SneakyThrows;
import org.springframework.stereotype.Component;
import org.telegram.telegrambots.bots.TelegramLongPollingBot;
import org.telegram.telegrambots.meta.api.methods.send.SendMessage;
import org.telegram.telegrambots.meta.api.objects.Document;
import org.telegram.telegrambots.meta.api.objects.Update;
import org.telegram.telegrambots.meta.exceptions.TelegramApiException;

import java.util.Objects;

@Component
public class LetiPrintBot extends TelegramLongPollingBot {

    final BotConfig config;

    HttpController httpController = new HttpController();

    public LetiPrintBot(BotConfig config) {
        this.config = config;
    }

    @Override
    public String getBotUsername() {
        return config.getBotName();
    }

    @Override
    public String getBotToken() {
        return config.getToken();
    }

    @SneakyThrows
    @Override
    public void onUpdateReceived(Update update) {

        if (update.hasMessage() && update.getMessage().hasDocument()) {
            Document fileReferences = update.getMessage().getDocument();
            String fileId = fileReferences.getFileId();
            String filePath = httpController.getFilePath(getBotToken(), fileId);
            if (!Objects.equals(filePath, "404"))
                httpController.sendDownloadLink(filePath, update.getMessage().getChatId(), getBotToken());
            else
                sendMessage(update.getMessage().getChatId(), "К сожалению, отправить файл не удалось. Повторите попытку позже");
            if (update.hasMessage() && update.getMessage().hasText()) {

                long chatId = update.getMessage().getChatId();
                String messageText = update.getMessage().getText();

                switch (messageText) {
                    case "/start" -> startCommandReceived(chatId);
                }


            }

        }
    }

    private void startCommandReceived(long chatId) {

        String answer = """
                LetiPrint - бот сервиса автономной печати.

                Отправьте файл, который хотите распечатать
                Далее вам будет отправлен четырехзначный код, который нужно ввести на станции печати

                После ввода кода, нажмите #,чтобы подтвердить ввод, чтобы удалить введенный код нажмите *""";


        sendMessage(chatId, answer);
    }

    private void sendMessage(long chatId, String textToSend) {
        SendMessage message = new SendMessage();
        message.setChatId(String.valueOf(chatId));
        message.setText(textToSend);

        try {
            execute(message);
        } catch (TelegramApiException ignored) {

        }

    }
}

