package com.example.letiprintbot.service;

import com.example.letiprintbot.config.BotConfig;
import com.example.letiprintbot.httpClient.HttpController;
import lombok.SneakyThrows;
import org.springframework.stereotype.Component;
import org.telegram.telegrambots.bots.TelegramLongPollingBot;
import org.telegram.telegrambots.meta.api.methods.send.SendMessage;
import org.telegram.telegrambots.meta.api.objects.Document;
import org.telegram.telegrambots.meta.api.objects.Update;
import org.telegram.telegrambots.meta.api.objects.replykeyboard.InlineKeyboardMarkup;
import org.telegram.telegrambots.meta.api.objects.replykeyboard.buttons.InlineKeyboardButton;
import org.telegram.telegrambots.meta.exceptions.TelegramApiException;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

@Component
public class LetiPrintBot extends TelegramLongPollingBot {

    final BotConfig config;

    HttpController httpController = new HttpController();

    String filename = null;

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

        if (update.hasCallbackQuery()) {
            String callData = update.getCallbackQuery().getData();
            if (!Objects.equals(callData, "noConfirm")) {
                String printCode = httpController.sendMetadata(getBotToken(), callData, filename,update.getCallbackQuery().getFrom().getId().toString());
                String answer = "Файл успешно отправлен на принтер. Для печати введите код " + printCode + "\n" + "Не забудьте нажать # для подтверждение ввода кода";
                sendMessage(update.getCallbackQuery().getFrom().getId(), answer);
            } else
                sendMessage(update.getCallbackQuery().getFrom().getId(), "Отправка файла отменена");
        }

        if (update.hasMessage() && update.getMessage().hasDocument()) {
            Document fileReferences = update.getMessage().getDocument();
            String fileId = fileReferences.getFileId();
            String filePath = httpController.getFilePath(getBotToken(), fileId);
            filename = fileReferences.getFileName();

            sendFileConfirm(update.getMessage().getChatId(), filePath);

        }

        if (update.hasMessage() && update.getMessage().hasText()) {

            long chatId = update.getMessage().getChatId();
            String messageText = update.getMessage().getText();

            switch (messageText) {
                case "/start" -> startCommandReceived(chatId);
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

    private void sendFileConfirm(long chatId, String filePath) throws TelegramApiException {
        SendMessage message = new SendMessage();
        message.setChatId(String.valueOf(chatId));
        InlineKeyboardMarkup inlineKeyboardMarkup = new InlineKeyboardMarkup();
        InlineKeyboardButton yesButton = new InlineKeyboardButton();
        InlineKeyboardButton noButton = new InlineKeyboardButton();
        yesButton.setText("Да");
        noButton.setText("Нет");
        yesButton.setCallbackData(filePath);
        noButton.setCallbackData("noConfirm");
        List<InlineKeyboardButton> inlineKeyboardButtonList = new ArrayList<>();
        inlineKeyboardButtonList.add(yesButton);
        inlineKeyboardButtonList.add(noButton);
        List<List<InlineKeyboardButton>> keyBoardButtons = new ArrayList<>();
        keyBoardButtons.add(inlineKeyboardButtonList);
        inlineKeyboardMarkup.setKeyboard(keyBoardButtons);
        message.setText("Вы действительно хотите распечатать этот файл?");
        message.setReplyMarkup(inlineKeyboardMarkup);
        execute(message);
    }

}

